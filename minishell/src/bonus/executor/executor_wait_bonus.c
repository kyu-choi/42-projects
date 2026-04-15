/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_wait_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_bonus.h"

/**
 * @brief Waits for child and returns exit status
 * @param pid Child process ID
 * @param path Command path to free
 * @return Exit status
 */
int	wait_and_get_status(pid_t pid, char *path)
{
	int	status;

	setup_signals_exec();
	waitpid(pid, &status, 0);
	setup_signals();
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		print_signal_msg(WTERMSIG(status));
		return (128 + WTERMSIG(status));
	}
	return (status);
}
