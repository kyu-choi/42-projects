/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:16:51 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:16:58 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	intdigit(long long k)
{
	int	count;

	count = 0;
	if (k < 0)
	{
		count++;
		k = k * -1;
	}
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

static	void	numinput(long long k, char *res, int size)
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
	if (k < 0)
	{
		size--;
		res[i++] = '-';
		k = k * -1;
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

char	*ft_itoa(int n)
{
	int			size;
	long long	k;
	char		*res;

	k = (long long)n;
	size = intdigit(k);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	numinput(k, res, size);
	return (res);
}

int	printint(va_list args)
{
	int		count;
	int		num;
	char	*str;
	char	*a;

	count = 0;
	num = va_arg(args, int);
	str = ft_itoa(num);
	a = str;
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	free(a);
	return (count);
}
