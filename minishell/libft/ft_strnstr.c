/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:50:13 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/07/07 03:46:47 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man strnstr —  locate a substring in a string
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <string.h>
 *
 *      char *strnstr(const char *big, const char *little, size_t len);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The strnstr() function locates the first occurrence of the 
 * 	null-terminated string little in the string big, where not more than 
 * 	len characters are searched. Characters that appear after a ‘\0’ 
 * 	character are not searched. Since the strnstr() function is a FreeBSD 
 * 	specific API, it should only be used when portability is not a 
 * 	concern.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      If little is an empty string, big is returned; if little occurs 
 * 	nowhere in big, NULL is returned; otherwise a pointer to the first 
 * 	character of the first occurrence of little is returned.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (j < little_len && i + j < len
				&& big[i + j] && big[i + j] == little[j])
				++j;
			if (j == little_len)
				return ((char *)&big[i]);
		}
		++i;
	}
	return (NULL);
}
