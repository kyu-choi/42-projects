/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_unlink_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:50:54 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 21:50:55 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_unlink_free2(void)
{
	sem_unlink("/ph_forks");
	sem_unlink("/ph_gate");
	sem_unlink("/ph_print");
	sem_unlink("/ph_dead");
	sem_unlink("/ph_full");
	sem_unlink("/ph_start");
}

void	close_unlink_free(pid_t *pids, t_sems *sems)
{
	if (pids)
		free(pids);
	if (sems->forks)
		sem_close(sems->forks);
	if (sems->gate)
		sem_close(sems->gate);
	if (sems->print)
		sem_close(sems->print);
	if (sems->dead)
		sem_close(sems->dead);
	if (sems->full)
		sem_close(sems->full);
	if (sems->start)
		sem_close(sems->start);
	close_unlink_free2();
}
