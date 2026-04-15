/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:28:45 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:28:47 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_inform *inform)
{
	printf("0 1 has taken a fork\n");
	usleep(inform->time_to_die * 1000);
	printf("%d 1 died\n", inform->time_to_die);
}
