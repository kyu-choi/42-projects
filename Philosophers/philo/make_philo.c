/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:30:16 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:30:17 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(t_inform *inform, t_philo **philo, t_share *share, t_pack **pack)
{
	(*philo) = (t_philo *)malloc(sizeof(t_philo) * (inform->number_of_philo));
	if (!(*philo))
		return (-1);
	if (init_share(inform, share) == -1)
	{
		free(*philo);
		return (-1);
	}
	init_philo(philo, share);
	if (create_pthread(inform, philo, share, pack) == -1)
	{
		free_destroy(*philo, share, NULL);
		return (-1);
	}
	return (0);
}
