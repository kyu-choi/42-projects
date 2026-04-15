/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:38:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/02 18:15:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_strjoin - Concatenate two strings into a new one
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	char *ft_strjoin(const char *s1, const char *s2);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_strjoin() function allocates (with malloc) and returns a new 
 * 	string, which is the result of the concatenation of 's1' and 's2'. If 
 * 	either 's1' or 's2' is NULL, the function treats it as an empty 
 * 	string.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *  	The function returns the concatenated string, or NULL if the 
 * 	allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	return (result);
}
