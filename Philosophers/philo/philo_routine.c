/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:51:18 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:51:19 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_while(t_inform *inform, t_philo *philo,
t_share *share, int stopped)
{
	while (1)
	{
		pthread_mutex_lock(&share->state_mx);
		stopped = share->stop;
		pthread_mutex_unlock(&share->state_mx);
		if (stopped == 1)
			break ;
		take_forks(philo, share);
		pthread_mutex_lock(&philo->meal_mx);
		philo->last_meal = now_ms();
		pthread_mutex_unlock(&philo->meal_mx);
		print_action(share, philo->id, "is eating", 0);
		philo_action(inform->time_to_eat, share);
		pthread_mutex_lock(&philo->meal_mx);
		philo->eaten++;
		pthread_mutex_unlock(&philo->meal_mx);
		put_forks(philo, share);
		print_action(share, philo->id, "is sleeping", 0);
		philo_action(inform->time_to_sleep, share);
		print_action(share, philo->id, "is thinking", 0);
	}
}

void	*philo_routine(void *arg)
{
	t_inform	*inform;
	t_philo		*philo;
	t_share		*share;
	t_pack		*pack;
	int			stopped;

	pack = (t_pack *)arg;
	share = pack->share;
	inform = pack->inform;
	philo = pack->philo;
	if (philo->id % 2)
		usleep(200);
	stopped = 0;
	philo_while(inform, philo, share, stopped);
	return (NULL);
}
