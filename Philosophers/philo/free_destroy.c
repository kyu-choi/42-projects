/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:29:03 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 13:29:04 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_destroy(t_philo *philo, t_share *share, t_pack *pack)
{
	int	i;

	if (pack)
		free(pack);
	i = 0;
	while (i < share->n)
	{
		pthread_mutex_destroy(&philo[i].meal_mx);
		i++;
	}
	free(philo);
	i = 0;
	while (i < share->n)
	{
		pthread_mutex_destroy(&share->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&share->print_mx);
	pthread_mutex_destroy(&share->state_mx);
	free(share->forks);
	share->forks = NULL;
}
