/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:35:15 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 19:35:16 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	in_while(t_child *child)
{
	sem_wait(child->sems->gate);
	sem_wait(child->sems->forks);
	print_action(child->sems->print, child->id, \
	"has taken a fork", child->start_ms);
	sem_wait(child->sems->forks);
	print_action(child->sems->print, child->id, \
	"has taken a fork", child->start_ms);
	child->last_meal = now_ms();
	print_action(child->sems->print, child->id, "is eating", child->start_ms);
	philo_action(child->inform->time_to_eat);
	sem_post(child->sems->forks);
	sem_post(child->sems->forks);
	sem_post(child->sems->gate);
}

void	child_while(t_child *child, int eaten, int post)
{
	while (1)
	{
		in_while(child);
		if (child->inform->must == 1)
		{
			eaten++;
			if (post == 0 && eaten >= child->inform->number_of_must)
			{
				sem_post(child->sems->full);
				post = 1;
			}
		}
		print_action(child->sems->print, child->id, \
		"is sleeping", child->start_ms);
		philo_action(child->inform->time_to_sleep);
		print_action(child->sems->print, child->id, \
		"is thinking", child->start_ms);
		usleep(200);
	}
}

void	child_main(t_child *child)
{
	pthread_t	monitor;
	int			eaten;
	int			post;

	sem_wait(child->sems->start);
	child->start_ms = now_ms();
	child->last_meal = child->start_ms;
	pthread_create(&monitor, NULL, monitor_main, (void *)child);
	pthread_detach(monitor);
	eaten = 0;
	post = 0;
	child_while(child, eaten, post);
}
