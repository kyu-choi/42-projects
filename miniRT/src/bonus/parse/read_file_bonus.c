/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file read_file_bonus.c
 * @brief Reads an entire file into a heap-allocated buffer (bonus).
 *
 * Uses an exponential-doubling strategy: starts at 1024 bytes, doubles
 * on each realloc.  The first two size_t slots store capacity and
 * length metadata (hidden from the caller's returned pointer).
 */

/**
 * @brief Copy n bytes from src to dst.
 */
static void	rt_memcpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

/**
 * @brief Append n bytes to *buf; grow if needed. meta[0]=cap, meta[1]=len.
 * @return 1 on success; 0 on malloc fail.
 */
static int	rt_append(char **buf, int *meta, char *chunk, int n)
{
	char	*new_buf;
	int		new_cap;

	if (meta[1] + n + 1 >= meta[0])
	{
		new_cap = meta[0] * 2;
		while (new_cap <= meta[1] + n + 1)
			new_cap = new_cap * 2;
		new_buf = (char *)malloc(new_cap);
		if (!new_buf)
			return (0);
		rt_memcpy(new_buf, *buf, meta[1]);
		free(*buf);
		*buf = new_buf;
		meta[0] = new_cap;
	}
	rt_memcpy(*buf + meta[1], chunk, n);
	meta[1] = meta[1] + n;
	(*buf)[meta[1]] = '\0';
	return (1);
}

/**
 * @brief Read fd in 1K chunks; append to buf via rt_append.
 * @return 1 on success; 0 on read/append error.
 */
static int	rt_read_loop(int fd, char **buf, int *meta)
{
	char	tmp[1024];
	int		rd;

	rd = read(fd, tmp, 1024);
	while (rd > 0)
	{
		if (!rt_append(buf, meta, tmp, rd))
			return (0);
		rd = read(fd, tmp, 1024);
	}
	if (rd < 0)
		return (0);
	return (1);
}

/**
 * @brief Read entire file into nul-terminated heap string.
 * @param path File path.
 * @return Allocated string or NULL on error.
 */
char	*rt_read_file(char *path)
{
	int		fd;
	char	*buf;
	int		meta[2];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	meta[0] = 1024;
	meta[1] = 0;
	buf = (char *)malloc(meta[0]);
	if (!buf)
		return (close(fd), NULL);
	buf[0] = '\0';
	if (!rt_read_loop(fd, &buf, meta))
		return (close(fd), free(buf), NULL);
	close(fd);
	return (buf);
}
