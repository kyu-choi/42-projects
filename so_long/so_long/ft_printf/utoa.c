/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:24:45 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:24:51 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	intdigit(unsigned int k)
{
	int	count;

	count = 0;
	if (k == 0)
		return (1);
	while (k > 0)
	{
		k /= 10;
		count++;
	}
	return (count);
}

static	int	poww(int n, int m)
{
	int	num;

	m--;
	num = 1;
	while (m > 0)
	{
		num = num * n;
		m--;
	}
	return (num);
}

static	void	numinput(unsigned int k, char *res, int size)
{
	int	i;
	int	m;

	i = 0;
	if (k == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return ;
	}
	while (size > 0)
	{
		m = poww(10, size);
		res[i++] = '0' + (k / m);
		k = k % m;
		size--;
	}
	res[i] = '\0';
}

char	*utoa(unsigned int num)
{
	int		size;
	char	*res;

	size = intdigit(num);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	numinput(num, res, size);
	return (res);
}
