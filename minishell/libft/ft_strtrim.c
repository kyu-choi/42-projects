/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:22:29 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/01/07 17:30:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_strtrim - Trim specific characters from the start and end 
 * 	of a string
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	char *ft_strtrim(const char *s1, const char *set);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_strtrim() function allocates (with malloc) and returns a copy 
 * 	of 's1' with the characters specified in 'set' removed from the 
 * 	beginning and the end of the string. If 'set' is NULL, no characters 
 * 	are trimmed.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *  	The trimmed string, or NULL if the allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>

static bool	is_in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*result;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		++start;
	end = ft_strlen(s1);
	while (start < end && is_in_set(s1[end - 1], set))
		--end;
	len = end - start;
	result = malloc(len + 1);
	if (result)
		ft_strlcpy(result, s1 + start, len + 1);
	return (result);
}

static bool	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (true);
		++set;
	}
	return (false);
}
