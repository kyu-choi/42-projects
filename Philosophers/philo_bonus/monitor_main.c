/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:42:50 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 20:42:51 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_main(void *arg)
{
	long long	now;
	long long	last;
	t_child		*child;

	child = (t_child *)arg;
	while (1)
	{
		now = now_ms();
		last = child->last_meal;
		if (now - last >= child->inform->time_to_die)
		{
			print_died(child->sems->print, child->id, \
			child->start_ms, child->sems->dead);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
