/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:19:37 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:19:38 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	five_check(char *argv, t_inform *inform)
{
	int	val;

	val = ft_atoi(argv);
	if (val <= 0)
	{
		printf("Error\n");
		return (-1);
	}
	inform->must = 1;
	inform->number_of_must = val;
	return (0);
}
