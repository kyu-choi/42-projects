/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:10:18 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 03:21:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man memchr - scan memory for a character
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      void *memchr(const void *s, int c, size_t n);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The memchr() function scans the initial n bytes of the memory area 
 * 	pointed to by s for the first instance of c. Both c and the bytes of 
 * 	the memory area pointed to by s are interpreted as unsigned char.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      The memchr() function return a pointer to the matching byte or NULL 
 * 	if the character does not occur in the given memory area.
 * -------------------------------------------------------------------------- *
 */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	find_ch;
	size_t			i;

	src = (unsigned char *)s;
	find_ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == find_ch)
			return ((void *)&src[i]);
		++i;
	}
	return (NULL);
}
