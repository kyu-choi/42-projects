/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:05:57 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 13:05:58 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyone_full(t_inform *inform, t_philo *philo, t_share *share)
{
	int	i;
	int	eaten;

	if (inform->must == 0)
		return (0);
	i = 0;
	while (i < share->n)
	{
		pthread_mutex_lock(&philo[i].meal_mx);
		eaten = philo[i].eaten;
		pthread_mutex_unlock(&philo[i].meal_mx);
		if (eaten < inform->number_of_must)
			return (0);
		i++;
	}
	pthread_mutex_lock(&share->state_mx);
	share->stop = 1;
	pthread_mutex_unlock(&share->state_mx);
	return (1);
}

void	monitor_utill(t_philo *philo, t_var *var)
{
	pthread_mutex_lock(&philo[var->i].meal_mx);
	var->last = philo[var->i].last_meal;
	pthread_mutex_unlock(&philo[var->i].meal_mx);
	var->gap = now_ms() - var->last;
}

void	monitor_while(t_philo *philo, t_share *share, \
t_inform *inform, t_var *var)
{
	while (1)
	{
		var->i = 0;
		while (var->i < share->n)
		{
			monitor_utill(philo, var);
			if (var->gap > inform-> time_to_die)
			{
				pthread_mutex_lock(&share->state_mx);
				if (share->stop == 0)
				{
					share->stop = 1;
					pthread_mutex_unlock(&share->state_mx);
					print_action(share, philo[var->i].id, "died", 1);
				}
				else
					pthread_mutex_unlock(&share->state_mx);
				return ;
			}
			var->i++;
		}
		if (everyone_full(inform, philo, share) == 1)
			return ;
	}
}

void	*monitor_routine(void *arg)
{
	t_inform	*inform;
	t_philo		*philo;
	t_share		*share;
	t_pack		*pack;
	t_var		var;

	pack = (t_pack *)arg;
	share = pack->share;
	inform = pack->inform;
	philo = pack->philo;
	var.i = 0;
	monitor_while(philo, share, inform, &var);
	return (NULL);
}
