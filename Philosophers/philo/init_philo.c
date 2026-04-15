/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:40:18 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:40:19 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo **philo, t_share *share)
{
	int	i;

	i = 0;
	while (i < share->n)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % share->n;
		(*philo)[i].last_meal = share->start_ms;
		(*philo)[i].eaten = 0;
		pthread_mutex_init(&(*philo)[i].meal_mx, NULL);
		i++;
	}
}
