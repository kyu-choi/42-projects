/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   must.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:23:25 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:23:26 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	non_must(char **argv, t_inform *inform)
{
	if (one_check(argv[1], inform) == -1)
		return (-1);
	if (two_check(argv[2], inform) == -1)
		return (-1);
	if (three_check(argv[3], inform) == -1)
		return (-1);
	if (four_check(argv[4], inform) == -1)
		return (-1);
	inform->must = 0;
	return (0);
}

int	must_exit(char **argv, t_inform *inform)
{
	if (one_check(argv[1], inform) == -1)
		return (-1);
	if (two_check(argv[2], inform) == -1)
		return (-1);
	if (three_check(argv[3], inform) == -1)
		return (-1);
	if (four_check(argv[4], inform) == -1)
		return (-1);
	if (five_check(argv[5], inform) == -1)
		return (-1);
	inform->must = 1;
	return (0);
}
