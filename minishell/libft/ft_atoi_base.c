/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:42:13 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:43:37 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* % ft_atoi_base - convert a string to an integer in specified base
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *	The ft_atoi_base() function converts the initial portion of the string
 *	pointed to by str to int representation in the specified base.
 *	Supports bases from 2 to 16.
 *
 *	For bases greater than 10:
 *	- 'a'-'f' or 'A'-'F' represent values 10-15
 *
 *	The conversion stops at the first character that is not a valid digit
 *	in the given base.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *	The converted integer value.
 *	Returns 0 if base is invalid (< 2 or > 16).
 * -------------------------------------------------------------------------- *
 */
int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	digit;

	result = 0;
	if (base < 2 || base > 16)
		return (0);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
	return (result);
}
