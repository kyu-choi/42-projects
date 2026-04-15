/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Prepares all heredocs before execution
 * @param cmds Command list
 * @param shell Shell state for variable expansion
 * @return 0 on success, -1 on error or interrupt
 * @details Processes all heredocs upfront to match bash behavior
 */
int	prepare_all_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	t_redir	*redir;

	current = cmds;
	while (current)
	{
		redir = current->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_REDIR_HEREDOC)
			{
				if (handle_heredoc(redir, shell) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Counts number of commands in pipeline
 * @param cmds Command linked list
 * @return Number of commands
 */
int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

/**
 * @brief Updates _ environment variable with command path for pipeline
 * @param shell Shell state
 * @param cmd_name Command name to find path for
 * @details Only updates for external commands, skips builtins
 */
void	update_underscore_pipe(t_shell *shell, char *cmd_name)
{
	char	*path;

	if (is_builtin(cmd_name))
		return ;
	path = find_command_path(cmd_name, shell->env);
	if (path)
	{
		set_env_value(&shell->env, "_", path, 1);
		free(path);
	}
}

/**
 * @brief Sets up input and output file descriptors for pipeline
 * @param in_fd Input file descriptor to redirect from
 * @param out_fd Output file descriptor to redirect to
 */
void	setup_pipe_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

/**
 * @brief Executes external command with environment variables
 * @param cmd_name Command name or path
 * @param args Argument array
 * @param env Environment variable list
 * @details Does not return on success, exits on failure
 */
void	exec_external_cmd(char *cmd_name, char **args, t_env *env)
{
	char	**envp;
	char	*path;

	path = find_command_path(cmd_name, env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	envp = env_to_array_util(env);
	execve(path, args, envp);
	exit(127);
}
