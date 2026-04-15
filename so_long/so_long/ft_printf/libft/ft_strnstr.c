/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:47 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:56:43 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *sea, size_t n)
{
	size_t		i;
	int			j;
	char		*res;

	if (!src && !sea)
		return (NULL);
	if (*sea == '\0')
		return ((char *)src);
	i = 0;
	j = 0;
	while ((i < n) && src[i])
	{
		j = 0;
		if (src[i] == sea[0])
		{
			res = (char *)&src[i];
			while (src[i + j] == sea[j] && i + j < n && src[i + j] && sea[j])
				j++;
			if (sea[j] == '\0')
				return (res);
		}
		i++;
	}
	return (NULL);
}
