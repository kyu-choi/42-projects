/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:41:13 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 14:41:14 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_inform	inform;
	t_sems		sems;
	pid_t		*pids;

	if (argv_check(argc, argv, &inform) == -1)
		return (0);
	if (inform.number_of_philo == 1)
	{
		one_philo(&inform);
		return (0);
	}
	if (sema_init(&sems, &inform, &pids) == -1)
		return (1);
	if (make_child(inform.n, pids, &inform, &sems) == -1)
		return (1);
	start_child(&sems, inform.n);
	if (inform.must == 1)
		full_monitor_start(&inform, &sems);
	sem_wait(sems.dead);
	kill_all(pids, inform.n, SIGTERM);
	usleep(1000);
	wait_all(pids, inform.n);
	close_unlink_free(pids, &sems);
}
