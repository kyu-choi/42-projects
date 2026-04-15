/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_bonus.h"

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
 * @brief Executes a subshell command from token list
 * @param tokens Token list for subshell
 * @param shell Shell state
 * @return Exit status of subshell execution
 */
int		execute_subshell_cmd(t_token *tokens, t_shell *shell);

/**
 * @brief Counts the number of commands in the pipeline
 * @param cmds Command linked list
 * @return Number of commands
 */
static int	count_cmds(t_cmd *cmds)
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
 * @brief Executes a single command in the pipeline with redirections
 * @param cmd Command structure
 * @param shell Shell state
 * @param in_fd Input file descriptor
 * @param out_fd Output file descriptor
 */
static void	exec_pipe_cmd(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd)
{
	int	ret;

	setup_pipe_fds(in_fd, out_fd);
	close_unused_fds();
	if (apply_redirections(cmd->redirs, shell) < 0)
		exit(1);
	if (cmd->is_subshell)
	{
		ret = execute_subshell_cmd(cmd->subshell_tokens, shell);
		exit(ret);
	}
	if (!cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(shell, cmd));
	exec_external_cmd(cmd->args[0], cmd->args, shell->env);
	exit(127);
}

/**
 * @brief Forks and executes a command in child process
 * @param cmd Command to execute
 * @param shell Shell state
 * @param in Input file descriptor
 * @param out Output file descriptor
 * @return Child process ID
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
 * @param shell Shell state
 * @param cmds Command linked list
 * @param pids Array to store child process IDs
 */
static void	exec_cmds_loop(t_shell *shell, t_cmd *cmds, pid_t *pids)
{
	int	pipe_fd[2];
	int	in_fd;
	int	out_fd;
	int	i;

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
		if (cmds->next)
		{
			close(pipe_fd[1]);
			in_fd = pipe_fd[0];
		}
		cmds = cmds->next;
	}
}

/**
 * @brief Executes a pipeline of commands
 * @param shell Shell state
 * @param cmds Command linked list representing pipeline
 * @return Exit status of last command in pipeline
 */
int	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	pid_t	*pids;
	int		count;
	int		ret;

	count = count_cmds(cmds);
	pids = malloc(sizeof(pid_t) * count);
	setup_signals_exec();
	exec_cmds_loop(shell, cmds, pids);
	ret = wait_for_pids(pids, count);
	setup_signals();
	return (ret);
}
