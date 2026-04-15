/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:05:52 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 16:05:53 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sema_init(t_sems *sems, t_inform *inform, pid_t **pids)
{
	sem_unlink("/ph_forks");
	sem_unlink("/ph_gate");
	sem_unlink("/ph_print");
	sem_unlink("/ph_dead");
	sem_unlink("/ph_full");
	sem_unlink("/ph_start");
	inform->n = inform->number_of_philo;
	sems->forks = sem_open("/ph_forks", O_CREAT | O_EXCL, 0644, inform->n);
	sems->gate = sem_open("/ph_gate", O_CREAT | O_EXCL, 0644, inform->n / 2);
	sems->print = sem_open("/ph_print", O_CREAT | O_EXCL, 0644, 1);
	sems->dead = sem_open("/ph_dead", O_CREAT | O_EXCL, 0644, 0);
	sems->full = sem_open("/ph_full", O_CREAT | O_EXCL, 0644, 0);
	sems->start = sem_open("/ph_start", O_CREAT | O_EXCL, 0644, 0);
	if (init_check(sems) == -1)
		return (-1);
	*pids = (pid_t *)malloc(sizeof(pid_t) * inform->n);
	if (!(*pids))
	{
		close_unlink_free(NULL, sems);
		return (-1);
	}
	return (0);
}
