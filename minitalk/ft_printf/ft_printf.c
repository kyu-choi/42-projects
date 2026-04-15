/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:52:52 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 16:53:15 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	format(char src, va_list args)
{
	int	count;

	if (src == 'c')
		count = printchar(args);
	else if (src == 's')
		count = printstr(args);
	else if (src == 'p')
		count = printpoint(args);
	else if (src == 'd' || src == 'i')
		count = printint(args);
	else if (src == 'u')
		count = printunsigned(args);
	else if (src == 'x')
		count = printlowhex(args);
	else if (src == 'X')
		count = printuphex(args);
	else if (src == '%')
	{
		write(1, "%", 1);
		count = 1;
	}
	else
		count = -1;
	return (count);
}

static	int	whilesrc(const char *src, int count, va_list args)
{
	int	result;

	while (*src)
	{
		if (*src == '%')
		{
			src++;
			result = format(*src, args);
			if (result == -1)
			{
				va_end(args);
				return (-1);
			}
			count = count + result;
			src++;
		}
		else
		{
			write(1, src, 1);
			src++;
			count++;
		}
	}
	return (count);
}

int	ft_printf(const char *src, ...)
{
	int			count;
	va_list		args;

	count = 0;
	va_start(args, src);
	count = whilesrc(src, count, args);
	va_end(args);
	return (count);
}
