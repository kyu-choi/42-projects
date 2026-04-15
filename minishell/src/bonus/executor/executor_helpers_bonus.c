/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
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
 * @brief Checks if redirections contain heredoc
 * @param redirs Redirection list to check
 * @return 1 if heredoc found, 0 otherwise
 */
int	has_heredoc(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (current->type == TOKEN_REDIR_HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Executes external command in child process
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @param path Full path to executable
 * @details Sets up signals, converts env to array, executes via execve
 */
void	execute_child(t_shell *shell, t_cmd *cmd, char *path)
{
	char		**envp;
	struct stat	path_stat;

	setup_signals_child();
	envp = env_to_array_util(shell->env);
	execve(path, cmd->args, envp);
	ft_free_split(envp);
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (access(path, X_OK) == -1 && errno == EACCES)
	{
		perror("minishell");
		exit(126);
	}
	perror("minishell");
	exit(127);
}
