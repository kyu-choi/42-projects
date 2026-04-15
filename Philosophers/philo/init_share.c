/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_share.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:33:31 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:33:32 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

int	init_share(t_inform *inform, t_share *share)
{
	int	i;

	share->n = inform->number_of_philo;
	share->stop = 0;
	share->forks = malloc(sizeof(pthread_mutex_t) * share->n);
	if (!share->forks)
		return (-1);
	i = 0;
	while (i < share->n)
	{
		pthread_mutex_init(&(share->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(share->print_mx), NULL);
	pthread_mutex_init(&(share->state_mx), NULL);
	share->start_ms = now_ms();
	return (0);
}
