/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:54:24 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Calculates the number of digits in an unsigned integer.
static int	count_digits(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}

// Converts an unsigned integer to a string.
char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		len;

	len = count_digits(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		--len;
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

// Calculates the number of hex digits in an unsigned long.
static int	count_hex_digits(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		++count;
	}
	return (count);
}

// Converts an unsigned long to a hexadecimal tring.
// The `specifier` determines if the output is lowercase('x') or uppercase('X').
char	*ft_ultoa_hex(unsigned long nbr, char specifier)
{
	char	*hex_chars;
	char	*str;
	int		len;

	len = count_hex_digits(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (specifier == 'x')
		hex_chars = "0123456789abcdef";
	else
		hex_chars = "0123456789ABCDEF";
	while (nbr > 0)
	{
		--len;
		str[len] = hex_chars[nbr % 16];
		nbr /= 16;
	}
	return (str);
}
