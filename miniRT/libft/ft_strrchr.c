/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:00:11 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 03:36:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man strrchr - locate character in string 
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      char *strrchr(const char *s, int c);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The strrchr() function returns a pointer to the last occurrence of 
 * 	the character c in the string s.
 * 
 * 	Here "character" means "byte"; this function do not work with wide or 
 * 	multibyte characters.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The strrchr() function return a pointer to the matched character or 
 * 	NULL if the character is not found. The terminating null byte is 
 * 	considered part of the string, so that if c is specified as '\0', 
 * 	these functions return a pointer to the terminator.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	find_ch;

	find_ch = (unsigned char)c;
	i = ft_strlen(s) + 1;
	while (i > 0)
	{
		--i;
		if (s[i] == find_ch)
			return ((char *)&s[i]);
	}
	return (NULL);
}
