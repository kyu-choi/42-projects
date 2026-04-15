/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:44:11 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:44:12 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_pthread(t_inform *inform, t_philo **philo,
t_share *share, t_pack **pack)
{
	int	i;

	(*pack) = (t_pack *)malloc(sizeof(t_pack) * share->n);
	if (!(*pack))
		return (-1);
	i = 0;
	while (i < share->n)
	{
		(*pack)[i].share = share;
		(*pack)[i].inform = inform;
		(*pack)[i].philo = &(*philo)[i];
		i++;
	}
	i = 0;
	while (i < share->n)
	{
		pthread_create(&((*philo)[i].thread), NULL, philo_routine, &(*pack)[i]);
		i++;
	}
	return (0);
}
