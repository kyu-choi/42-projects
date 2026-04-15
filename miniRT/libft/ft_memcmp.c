/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:39:47 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 04:39:57 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man memcmp - compare memory areas
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      int memcmp(const void *s1, const void *s2, size_t n);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The memcmp() function compares the first n bytes (each interpreted as 
 * 	unsigned char) of the memory areas s1 and s2.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The memcmp() function returns an integer less than, equal to, or 
 * 	greater than zero if the first n bytes of s1 is found, respectively, 
 * 	to be less than, to match, or be greater than the first n bytes of s2
 * 	.
 * 
 * 	For a nonzero return value, the sign is determined by the sign of the 
 * 	difference between the first pair of bytes (interpreted as unsigned 
 * 	char) that differ in s1 and s2.
 * 
 * 	If n is zero, the return value is zero.
 * -------------------------------------------------------------------------- *
 */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;

	if (s1 == s2 || n == 0)
		return (0);
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	i = 0;
	while (i < n && src1[i] == src2[i])
		++i;
	if (i == n)
		return (0);
	return ((int)(src1[i] - src2[i]));
}
