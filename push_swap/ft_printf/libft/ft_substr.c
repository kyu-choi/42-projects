/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:43:54 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 18:52:57 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;
	size_t	size;
	size_t	total;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size <= start)
		return (ft_strdup(""));
	if (size >= start + len)
		total = len;
	else
		total = size - start;
	res = (char *)malloc(sizeof(char) * (total + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < total)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
