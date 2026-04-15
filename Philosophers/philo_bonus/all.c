/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:59:08 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 21:59:09 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(pid_t	*pids, int n, int signal)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
			kill(pids[i], signal);
		i++;
	}
}

void	wait_all(pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
			waitpid(pids[i], NULL, 0);
		i++;
	}
}
