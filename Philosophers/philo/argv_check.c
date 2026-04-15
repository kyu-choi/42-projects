/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:12:22 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 12:12:23 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	four_check(char *argv, t_inform *inform)
{
	int	val;

	val = ft_atoi(argv);
	if (val <= 0)
	{
		printf("Error\n");
		return (-1);
	}
	inform->time_to_sleep = val;
	return (0);
}

int	three_check(char *argv, t_inform *inform)
{
	int	val;

	val = ft_atoi(argv);
	if (val <= 0)
	{
		printf("Error\n");
		return (-1);
	}
	inform->time_to_eat = val;
	return (0);
}

int	two_check(char *argv, t_inform *inform)
{
	int	val;

	val = ft_atoi(argv);
	if (val <= 0)
	{
		printf("Error\n");
		return (-1);
	}
	inform->time_to_die = val;
	return (0);
}

int	one_check(char *argv, t_inform *inform)
{
	int	val;

	val = ft_atoi(argv);
	if (val <= 0)
	{
		printf("Error\n");
		return (-1);
	}
	inform->number_of_philo = val;
	return (0);
}

int	argv_check(int argc, char **argv, t_inform *inform)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (-1);
	}
	inform->must = 0;
	if (argc == 5)
	{
		if (non_must(argv, inform) == -1)
			return (-1);
	}
	else
	{
		if (must_exit(argv, inform) == -1)
			return (-1);
	}
	return (0);
}
