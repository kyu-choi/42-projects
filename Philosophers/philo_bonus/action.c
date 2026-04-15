/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:38:06 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 23:38:08 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_died(sem_t *print, int id, long long time, sem_t *dead)
{
	long long	now;

	now = now_ms() - time;
	sem_wait(print);
	printf("%lld %d died\n", now, id);
	sem_post(print);
	sem_post(dead);
}

void	print_action(sem_t *print, int id, char *msg, long long time)
{
	long long	now;

	now = now_ms() - time;
	sem_wait(print);
	printf("%lld %d %s\n", now, id, msg);
	sem_post(print);
}

void	philo_action(int time)
{
	long long	end;

	end = now_ms() + (long long)time;
	while (now_ms() < end)
		usleep(200);
}
