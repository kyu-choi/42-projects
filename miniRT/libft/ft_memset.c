/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:10:21 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/03/22 12:11:31 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man memset - fill memory with a constant byte
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *	#include <string.h>
 *
 *	void *memset(void *s, int c, size_t n);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *	The memset() function fills the first n bytes of the memory area 
 * 	pointed to by s with the constant byte c.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The memset() function returns a pointer to the memory area s.
 * -------------------------------------------------------------------------- *
 */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)s;
	i = 0;
	while (i < n)
		src[i++] = c;
	return (s);
}
