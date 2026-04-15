/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:37:17 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/10/03 21:37:18 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_check(t_sems *sems)
{
	if (sems->forks == SEM_FAILED || sems->gate == SEM_FAILED || \
	sems->print == SEM_FAILED || sems->dead == SEM_FAILED || \
	sems->full == SEM_FAILED || sems->start == SEM_FAILED)
	{
		close_unlink_free(NULL, sems);
		return (-1);
	}
	return (0);
}
