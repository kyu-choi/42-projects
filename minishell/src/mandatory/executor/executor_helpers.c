/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Restores stdin/stdout from backups
 * @param stdin_backup Backup file descriptor for stdin
 * @param stdout_backup Backup file descriptor for stdout
 */
void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

/**
 * @brief Executes redirection-only command (no arguments)
 * @param cmd Command with only redirections
 * @param shell Shell state
 * @return 0 on success, 1 on error
 */
int	execute_redir_only(t_cmd *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	ret = apply_redirections(cmd->redirs, shell);
	restore_fds(stdin_backup, stdout_backup);
	if (ret < 0)
		return (1);
	return (0);
}

/**
 * @brief Prepares all heredocs for a single command
 * @param cmd Command containing redirection list
 * @param shell Shell state for heredoc processing
 * @return 0 on success, -1 on error
 */
static int	prepare_cmd_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_HEREDOC)
		{
			if (handle_heredoc(redir, shell) < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief Prepares all heredocs for command list
 * @param cmds Command linked list
 * @param shell Shell state for heredoc processing
 * @return 0 on success, -1 on error
 */
int	prepare_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (prepare_cmd_heredocs(current, shell) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Executes command with redirections applied
 * @param shell Shell state
 * @param cmd Command to execute
 * @return Exit status of command
 */
int	exec_with_redir(t_shell *shell, t_cmd *cmd)
{
	int		stdin_backup;
	int		stdout_backup;
	int		ret;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirs, shell) < 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		ret = execute_builtin(shell, cmd);
	else
		ret = execute_external_cmd(shell, cmd);
	restore_fds(stdin_backup, stdout_backup);
	return (ret);
}
