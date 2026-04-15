/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:21:15 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 04:39:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man strncmp - compare two strings 
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      int strncmp(const char *s1, const char *s2, size_t n);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *	The strncmp() function compares only the first (at most) n bytes of 
 * 	s1 and s2. The locale is not taken into account (for a locale-aware 
 * 	comparison, see strcoll(3)). The comparison is done using unsigned
 * 	characters.
 * 
 * 	strncmp() returns an integer indicating the result of the comparison, 
 * 	as follows:
 * 
 *     • 0, if the s1 and s2 are equal;
 * 
 *     • a negative value if s1 is less than s2;
 * 
 *     • a positive value if s1 is greater than s2.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The strncmp() functions return an integer less than, equal to, or 
 * 	greater than zero if s1 (or the first n bytes thereof) is found, 
 * 	respectively, to be less than, to match, or be greater than s2.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;

	i = 0;
	if (s1 == s2 || n == 0)
		return (0);
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (i < n && src1[i] && src2[i] && src1[i] == src2[i])
		++i;
	if (i == n)
		return (0);
	return ((int)(src1[i] - src2[i]));
}
