/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Sets up input and output file descriptors for pipeline execution
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
 * @brief Executes an external command with environment variables
 * @param cmd_name Command name to execute
 * @param args Command arguments array
 * @param env Environment variables
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
