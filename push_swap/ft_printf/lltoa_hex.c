/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltoa_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:24:29 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:24:33 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*makearr(void)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * 17);
	while (i < 10)
	{
		res[i] = '0' + i;
		i++;
	}
	res[10] = 'a';
	res[11] = 'b';
	res[12] = 'c';
	res[13] = 'd';
	res[14] = 'e';
	res[15] = 'f';
	return (res);
}

static	char	*reverarr(char *res, char *sor, int p)
{
	int	q;

	q = 0;
	while (q < p)
	{
		res[2 + q] = sor[p - 1 - q];
		q++;
	}
	res[q + 2] = '\0';
	return (res);
}

char	*lltoa_hex(unsigned long long i)
{
	char	*hexbase;
	char	sor[20];
	char	*res;
	int		p;

	hexbase = makearr();
	p = 0;
	while (i > 0)
	{
		sor[p++] = hexbase[i % 16];
		i = i / 16;
	}
	res = (char *)malloc(sizeof(char) * (p + 3));
	if (!res)
		return (NULL);
	res[0] = '0';
	res[1] = 'x';
	res = reverarr(res, sor, p);
	free(hexbase);
	return (res);
}
