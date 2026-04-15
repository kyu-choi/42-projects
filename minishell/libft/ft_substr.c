/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:28:12 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/10 08:33:44 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_substr - Extract a substring from a given string
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *  	char *ft_substr(const char *s, unsigned int start, size_t len);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *  	The ft_substr() function allocates (with malloc) and returns a 
 * 	substring from the string 's'. The substring begins at index 'start' 
 * 	and is of maximum size 'len'. If 'start' is greater than the length 
 * 	of 's', the function returns an empty string.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The function returns the substring, or NULL if the allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*result;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		result = (char *)malloc(1);
		if (result)
			result[0] = '\0';
	}
	else
	{
		if (start + len > s_len)
			len = s_len - start;
		result = (char *)malloc(len + 1);
		if (result)
			ft_strlcpy(result, s + start, len + 1);
	}
	return (result);
}
