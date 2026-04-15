/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:47:48 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/28 12:47:50 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*full_main(void *arg)
{
	t_full	*full;
	int		collected;

	full = (t_full *)arg;
	collected = 0;
	while (collected < full->n)
	{
		sem_wait(full->full);
		collected++;
	}
	if (collected >= full->n)
		sem_post(full->dead);
	free(full);
	return (NULL);
}
