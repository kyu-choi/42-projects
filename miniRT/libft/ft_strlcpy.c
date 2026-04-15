/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:45:32 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 17:14:48 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man strlcpy - size-bounded string copying
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      size_t strlcpy(char *dst, const char *src, size_t size);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The strlcpy() function copies strings respectively. It is designed to 
 * 	be safer, more consistent, and less error prone replacements for 
 * 	strncpy(3). Unlike this function, strlcpy() takes the full size of the 
 * 	buffer (not just the length) and guarantee to NUL-terminate the 
 * 	result (as long as size is larger than 0 or, as long as there is at 
 * 	least one byte free in dst). Note that a byte for the NUL should be 
 * 	included in size. Also note that strlcpy() only operates on true “C” 
 * 	strings. This means that for strlcpy() src must be NUL-terminated.
 * 
 *	The strlcpy() function copies up to size - 1 characters from the 
 * 	NUL-terminated string src to dst, NUL-terminating the result.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The strlcpy() function returns the total length of the string it tried 
 * 	to create. For strlcpy() that means the length of src. 
 * 	While this may seem somewhat confusing, it was done to make 
 * 	truncation detection simple. 
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst || !src || size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (src_len);
}
