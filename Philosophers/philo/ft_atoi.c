/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:27:49 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 16:52:53 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int				sign;
	long long		sum;

	sum = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (*nptr < '0' || *nptr > '9')
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{
		sum = (sum * 10) + *nptr - '0';
		nptr++;
	}
	if (sum * sign < -2147483648 || 2147483647 < sum * sign)
		return (0);
	return ((int)(sum * sign));
}
/*
int	main(void)
{
	int num;
	char *ex = "123";
	
	num = ft_atoi(ex);
	printf("%d",num);
	
	return (0);
}
*/
