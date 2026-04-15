/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:23:27 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/26 23:23:46 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	strcount(const char *s)
{
	int		count;
	char	*t;

	t = (char *)s;
	count = 0;
	while (*t)
	{
		count++;
		t++;
	}
	return (count);
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		index;
	int		size;
	char	*res;

	if (!s || !f)
		return (NULL);
	index = 0;
	size = strcount(s);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (s[index])
	{
		res[index] = f(index, s[index]);
		index++;
	}
	res[index] = '\0';
	return (res);
}
