/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:15:11 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 17:15:12 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pid_zero(t_child *child, int i, t_inform *inform, t_sems *sems)
{
	child->id = (i + 1);
	child->inform = inform;
	child->sems = sems;
	child->start_ms = 0;
	child_main(child);
	exit(0);
}

void	pid_minus(pid_t *pids, int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		kill(pids[k], SIGTERM);
		k++;
	}
	k = 0;
	while (k < i)
	{
		waitpid(pids[k], NULL, 0);
		k++;
	}
}

int	make_child(int n, pid_t *pids, t_inform *inform, t_sems *sems)
{
	int		i;
	pid_t	pid;
	t_child	child;

	memset(pids, 0, sizeof(pid_t) * n);
	i = 0;
	while (i < n)
	{
		pid = fork();
		if (pid < 0)
		{
			pid_minus(pids, i);
			close_unlink_free(pids, sems);
			return (-1);
		}
		if (pid == 0)
			pid_zero(&child, i, inform, sems);
		pids[i] = pid;
		i++;
	}
	return (0);
}
