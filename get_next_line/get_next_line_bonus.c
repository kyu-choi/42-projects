/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:05:41 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/06/01 20:05:45 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	char	*update_remain(char **remain, char *buf)
{
	char	*temp;

	if (!*remain)
		*remain = ft_strdup(buf);
	else
	{
		temp = *remain;
		*remain = ft_strjoin(*remain, buf);
		free(temp);
	}
	return (*remain);
}

static	char	*whilestr(char **remain, int fd, char *res, size_t count)
{
	char	*buf;
	ssize_t	bufsize;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bufsize = read(fd, buf, BUFFER_SIZE);
	while (bufsize > 0)
	{
		buf[bufsize] = '\0';
		*remain = update_remain(remain, buf);
		count = 0;
		while ((*remain)[count] && (*remain)[count] != '\n')
			count++;
		if ((*remain)[count] == '\n')
		{
			res = ft_utils(remain, count);
			return (free(buf), res);
		}
		bufsize = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bufsize < 0)
		return (free(*remain), *remain = NULL, NULL);
	return (NULL);
}

static	char	*first_remain(char **remain)
{
	char	*res;
	size_t	count;

	if (!(*remain))
		return (NULL);
	count = 0;
	while ((*remain)[count] && (*remain)[count] != '\n')
		count++;
	if ((*remain)[count] == '\n')
	{
		res = ft_utils(remain, count);
		return (res);
	}
	return (NULL);
}

static	char	*final_remain(char **remain)
{
	char	*res;

	if (*remain && **remain)
	{
		res = ft_strdup(*remain);
		free(*remain);
		*remain = NULL;
		return (res);
	}
	free(*remain);
	*remain = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remain[1024];
	char		*res;
	char		*temp;
	size_t		count;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	res = first_remain(&remain[fd]);
	if (res)
		return (res);
	count = 0;
	temp = NULL;
	res = whilestr(&remain[fd], fd, temp, count);
	if (res)
		return (res);
	return (final_remain(&remain[fd]));
}
