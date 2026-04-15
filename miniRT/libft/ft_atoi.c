/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:55:16 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/15 22:46:12 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man atoi - convert a string to an integer
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <stdlib.h>
 *
 *      int atoi(const char *nptr);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The atoi() function converts the initial portion of the string 
 * 	pointed to by nptr to int. The behavior is the same as 
 * 
 * 		strtol(nptr, NULL, 10);
 *
 * 	except that atoi() does not detect errors.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      The converted value or 0 on error.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

#define CHAR_TO_INT_OFFSET '0'

static int	ft_get_sign_value(char c, size_t *index);

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	while (ft_isspace(nptr[i]))
		++i;
	sign = ft_get_sign_value(nptr[i], &i);
	result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - CHAR_TO_INT_OFFSET);
		++i;
	}
	return (sign * result);
}

static int	ft_get_sign_value(char c, size_t *index)
{
	if (c == '-')
	{
		*index += 1;
		return (-1);
	}
	if (c == '+')
		*index += 1;
	return (1);
}
