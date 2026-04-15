/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:38:12 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 03:20:47 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man memmove - copy memory area 
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      void *memmove(void *dest, const void *src, size_t n);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The memmove() function copies n bytes from memory area src to memory 
 * 	area dest. The memory areas may overlap: copying takes place as 
 * 	though the bytes in src are first copied into a temporary array that 
 * 	does not overlap src or dest, and the bytes are then copied from the 
 * 	temporary array to dest.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      The memmove() function returns a pointer to dest.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
		ft_memcpy(d, s, n);
	else
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			--i;
		}
	}
	return (dest);
}
