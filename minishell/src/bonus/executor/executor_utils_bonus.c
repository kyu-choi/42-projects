/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_bonus.c                             :+:      :+:    :+:   */
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
 * @brief Extracts exit code from process status
 * @param status Status from waitpid
 * @return Exit code (0-255) or 128+signal if terminated by signal
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
 * @brief Waits for one specific process
 * @param pid Process ID to wait for
 * @param status Pointer to store exit status
 * @return 0 always
 */
static int	wait_one_pid(pid_t pid, int *status)
{
	pid_t	wp;

	if (pid != -1)
	{
		wp = waitpid(pid, status, 0);
		while (wp == -1 && errno == EINTR)
			wp = waitpid(pid, status, 0);
		if (wp == -1)
			*status = 1 << 8;
	}
	return (0);
}

/**
 * @brief Waits for all pipeline processes
 * @param pids Array of process IDs
 * @param count Number of processes
 * @return Exit status of last process
 */
int	wait_for_pids(pid_t *pids, int count)
{
	int		i;
	int		status;
	int		exit_status;

	exit_status = 0;
	status = 0;
	i = 0;
	while (i < count)
	{
		wait_one_pid(pids[i], &status);
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
 * @brief Closes all file descriptors above stderr
 * @details Closes FDs from 3 to 1024 to prevent FD leaks in child processes
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
