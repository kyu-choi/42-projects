/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Sets up input/output file descriptors for pipeline execution
 * @param in_fd Input file descriptor
 * @param out_fd Output file descriptor
 */
void	setup_pipe_fds(int in_fd, int out_fd);

/**
 * @brief Executes an external command with given arguments
 * @param cmd_name Command name or path
 * @param args Argument array
 * @param env Environment variables
 */
void	exec_external_cmd(char *cmd_name, char **args, t_env *env);

/**
 * @brief Executes a single command in pipeline context
 * @param cmd Command to execute
 * @param shell Shell state
 * @param in_fd Input file descriptor
 * @param out_fd Output file descriptor
 * @details Called in child process for each pipeline command
 */
static void	exec_pipe_cmd(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd)
{
	setup_pipe_fds(in_fd, out_fd);
	if (apply_redirections(cmd->redirs, shell) < 0)
		exit(1);
	close_unused_fds();
	if (!cmd->args[0])
		exit(0);
	update_underscore_pipe(shell, cmd->args[0]);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(shell, cmd));
	exec_external_cmd(cmd->args[0], cmd->args, shell->env);
}

/**
 * @brief Forks and executes command with redirections
 * @param cmd Command to execute
 * @param shell Shell state with environment
 * @param in Input file descriptor
 * @param out Output file descriptor
 * @return Process ID of child
 */
static pid_t	fork_and_exec(t_cmd *cmd, t_shell *shell, int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_signals_child();
		exec_pipe_cmd(cmd, shell, in, out);
	}
	return (pid);
}

/**
 * @brief Executes all commands in pipeline with pipes
 * @param shell Shell state with environment
 * @param cmds Command linked list
 * @param pids Array to store process IDs
 * @details Creates pipes between commands, manages file descriptors
 */
static void	exec_cmds_loop(t_shell *shell, t_cmd *cmds, pid_t *pids)
{
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	int		i;

	in_fd = STDIN_FILENO;
	i = 0;
	while (cmds)
	{
		if (cmds->next)
			pipe(pipe_fd);
		out_fd = STDOUT_FILENO;
		if (cmds->next)
			out_fd = pipe_fd[1];
		pids[i++] = fork_and_exec(cmds, shell, in_fd, out_fd);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		if (cmds->next)
			in_fd = pipe_fd[0];
		cmds = cmds->next;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

/**
 * @brief Updates underscore for last command in pipeline
 * @param cmds Command list
 * @param shell Shell state
 */
static void	update_last_cmd_underscore(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*last_cmd;
	char	*path;

	last_cmd = cmds;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	if (last_cmd->args && last_cmd->args[0] && !is_builtin(last_cmd->args[0]))
	{
		path = find_command_path(last_cmd->args[0], shell->env);
		if (path)
		{
			set_env_value(&shell->env, "_", path, 1);
			free(path);
		}
	}
}

/**
 * @brief Executes multi-command pipeline
 * @param shell Shell state with environment
 * @param cmds Command pipeline linked list
 * @return Exit status of last command
 * @details Allocates pid array, executes all commands, waits for completion
 */
int	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	pid_t	*pids;
	int		count;
	int		exit_status;

	if (prepare_all_heredocs(cmds, shell) < 0)
		return (1);
	count = count_cmds(cmds);
	pids = malloc(sizeof(pid_t) * count);
	update_last_cmd_underscore(cmds, shell);
	setup_signals_exec();
	exec_cmds_loop(shell, cmds, pids);
	exit_status = wait_for_pids(pids, count);
	setup_signals();
	return (exit_status);
}
