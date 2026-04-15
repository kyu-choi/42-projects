/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:06:14 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 21:06:15 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_child(t_sems *sems, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_post(sems->start);
		i++;
	}
}
