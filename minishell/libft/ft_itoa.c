/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:21:06 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/01/07 17:17:25 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_itoa - Convert an integer to a string
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	char *ft_itoa(int n);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_itoa() function allocates (with malloc) and returns a string 
 * 	representing the integer 'n'. Negative numbers must be handled 
 * 	properly, including the '-' sign for negative values.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The string representing the integer, or NULL if the allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>

static int	get_len(long long int n);

char	*ft_itoa(int n)
{
	int				len;
	long long int	num;
	char			*res;

	num = (long long int)n;
	len = get_len(num);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (num < 0)
	{
		res[0] = '-';
		num = -num;
	}
	if (num == 0)
		res[--len] = '0';
	while (num > 0)
	{
		res[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}

static int	get_len(long long int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		++len;
	}
	while (n >= 10)
	{
		n /= 10;
		++len;
	}
	return (len);
}
