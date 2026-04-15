/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:52:47 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 03:34:51 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man strchr - locate character in string 
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      char *strchr(const char *s, int c);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The strchr() function returns a pointer to the first occurrence of 
 * 	the character c in the string s.
 * 
 * 	Here "character" means "byte"; this function do not work with wide 
 * 	or multibyte characters.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      The strchr() function return a pointer to the matched character or 
 * 	NULL if the character is not found. The terminating null byte is 
 * 	considered part of the string, so that if c is specified as '\0', 
 * 	these functions return a pointer to the terminator.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h" 

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	find_ch;

	find_ch = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == find_ch)
			return ((char *)&s[i]);
		++i;
	}
	if (find_ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
