/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:16:52 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/26 13:16:53 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo, t_share *share)
{
	int	first;
	int	second;

	if (philo->left < philo->right)
	{
		first = philo->left;
		second = philo->right;
	}
	else
	{
		first = philo->right;
		second = philo->left;
	}
	pthread_mutex_lock(&share->forks[first]);
	print_action(share, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&share->forks[second]);
	print_action(share, philo->id, "has taken a fork", 0);
}

void	put_forks(t_philo *philo, t_share *share)
{
	int	first;
	int	second;

	if (philo->left < philo->right)
	{
		first = philo->left;
		second = philo->right;
	}
	else
	{
		first = philo->right;
		second = philo->left;
	}
	pthread_mutex_unlock(&share->forks[second]);
	pthread_mutex_unlock(&share->forks[first]);
}
