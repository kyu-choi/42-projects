/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_HEX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:43:23 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 20:43:52 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*makebase(void)
{
	return ("0123456789ABCDEF");
}

static	void	reverarr(char *res, char *des, int p)
{
	int	q;

	q = 0;
	while (q < p)
	{
		res[q] = des[p - 1 - q];
		q++;
	}
	res[q] = '\0';
}

static	void	zero(char *res)
{
	res[0] = '0';
	res[1] = '\0';
}

char	*utoa_uphex(unsigned int i)
{
	char	des[20];
	char	*res;
	char	*hexbase;
	int		p;

	if (i == 0)
	{
		res = (char *)malloc(sizeof(char) * 2);
		if (!res)
			return (NULL);
		zero(res);
		return (res);
	}
	hexbase = makebase();
	p = 0;
	while (i > 0)
	{
		des[p++] = hexbase[i % 16];
		i = i / 16;
	}
	res = (char *)malloc(sizeof(char) * (p + 1));
	if (!res)
		return (NULL);
	reverarr(res, des, p);
	return (res);
}
