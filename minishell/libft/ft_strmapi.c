/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:30:56 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/01/07 20:44:40 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_strmapi - Apply a function to each character of a string
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	char *ft_strmapi(const char *s, char (*f)(unsigned int, char));
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_strmapi() function applies the function 'f' to each character 
 * 	of the string 's', passing its index as the first argument. A new 
 * 	string is created with the successive applications of 'f'. If 's' is 
 * 	NULL, the function returns NULL.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The modified string, or NULL if the allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	i;
	char	*result;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	result = (char *)malloc(s_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		result[i] = f(i, s[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}
