/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:08:09 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/01/07 20:40:58 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man strdup - duplicate a string
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      char *strdup(const char *s);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The strdup() function returns a pointer to a new string which is a 
 * 	duplicate of the string s. Memory for the new string is obtained with 
 * 	malloc(3), and can be freed with free(3).
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	On success, the strdup() function returns a pointer to the duplicated 
 * 	string. It returns NULL if insufficient memory was available, with 
 * 	errno set to indicate the cause of the error.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*result;

	s_len = ft_strlen(s);
	result = (char *)malloc(s_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, s_len + 1);
	return (result);
}
