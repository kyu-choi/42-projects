/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_monitor_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:10:14 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/28 12:10:15 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	full_monitor_start(t_inform *inform, t_sems *sems)
{
	pthread_t	full_monitor;
	t_full		*full;

	full = malloc(sizeof(t_full));
	if (!full)
		return ;
	full->n = inform->number_of_philo;
	full->full = sems->full;
	full->dead = sems->dead;
	pthread_create(&full_monitor, NULL, full_main, full);
	pthread_detach(full_monitor);
}
