/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:51:39 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:56:13 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		count;
	char		*cpy;

	cpy = (char *)src;
	count = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while ((i < size - 1) && cpy[i])
		{
			dst[i] = cpy[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}
