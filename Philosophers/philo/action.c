/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:58:56 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:58:57 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_share *share, int id, char *msg, int is_dead)
{
	long long	time;
	int			stop;

	time = now_ms() - share->start_ms;
	pthread_mutex_lock(&share->print_mx);
	if (is_dead == 0)
	{
		pthread_mutex_lock(&share->state_mx);
		stop = share->stop;
		pthread_mutex_unlock(&share->state_mx);
		if (stop == 1)
		{
			pthread_mutex_unlock(&share->print_mx);
			return ;
		}
	}
	printf("%lld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&share->print_mx);
}

void	philo_action(long long ms, t_share *share)
{
	long long	end;
	int			stop;

	end = now_ms() + ms;
	while (now_ms() < end)
	{
		pthread_mutex_lock(&share->state_mx);
		stop = share->stop;
		pthread_mutex_unlock(&share->state_mx);
		if (stop == 1)
			break ;
		usleep(200);
	}
}
