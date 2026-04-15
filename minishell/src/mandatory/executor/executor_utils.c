/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/wait.h>

/**
 * @brief Extracts exit code from process status
 * @param status Status value from waitpid
 * @return Exit code (0-255 for normal exit, 128+signal for signals)
 */
static int	extract_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		if (WTERMSIG(status) != SIGPIPE)
			return (128 + WTERMSIG(status));
	}
	return (0);
}

/**
 * @brief Waits for all child processes in pipeline
 * @param pids Array of process IDs
 * @param count Number of processes
 * @return Exit status of last process
 * @details Frees pids array after waiting
 */
int	wait_for_pids(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
	status = 0;
	i = 0;
	while (i < count)
	{
		if (pids[i] != -1)
		{
			while (waitpid(pids[i], &status, 0) == -1 && errno == EINTR)
				;
		}
		if (i == count - 1)
		{
			if (pids[i] == -1)
				exit_status = 1;
			else
				exit_status = extract_exit_code(status);
		}
		i++;
	}
	free(pids);
	return (exit_status);
}

/**
 * @brief Closes all file descriptors >= 3
 * @details Prevents FD leaks in child processes
 */
void	close_unused_fds(void)
{
	int	fd;
	int	max_fd;

	max_fd = 1024;
	fd = 3;
	while (fd < max_fd)
		close(fd++);
}

/**
 * @brief Prints signal termination message
 * @param sig Signal number
 */
void	print_signal_msg(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}
