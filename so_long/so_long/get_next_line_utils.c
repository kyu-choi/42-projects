/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:21:15 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/06/01 10:21:18 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_utils(char **remain, size_t count)
{
	char	*temp;
	char	*res;

	res = ft_substr(*remain, 0, count + 1);
	temp = *remain;
	*remain = ft_substr(*remain, count + 1, ft_strlen(*remain));
	free(temp);
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;
	char	*res;

	res = (char *)str;
	len = 0;
	if (!res)
		return (0);
	while (*res)
	{
		res++;
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		count;
	char	*res;

	count = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size2)
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
