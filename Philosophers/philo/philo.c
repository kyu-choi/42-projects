/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:07:23 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:07:24 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_inform	inform;
	t_share		share;
	t_philo		*philo;
	t_pack		*pack;
	pthread_t	monitor;

	if (argv_check(argc, argv, &inform) == -1)
		return (0);
	if (inform.number_of_philo == 1)
	{
		one_philo(&inform);
		return (0);
	}
	if (make_philo(&inform, &philo, &share, &pack) == -1)
		return (1);
	pthread_create(&monitor, NULL, monitor_routine, pack);
	pthread_join(monitor, NULL);
	share.i = 0;
	while (share.i < share.n)
	{
		pthread_join(philo[share.i].thread, NULL);
		share.i++;
	}
	free_destroy(philo, &share, pack);
	return (0);
}
