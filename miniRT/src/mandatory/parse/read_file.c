/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file read_file.c
 * @brief Reads an entire file into a heap-allocated string.
 *
 * Uses a dynamically growing buffer with exponential doubling:
 * - Initial capacity: 1024 bytes
 * - Doubles when full (amortized O(1) per byte)
 * - Final string is NUL-terminated
 *
 * This approach avoids two passes (one to get the size, one to read)
 * and works with non-seekable file descriptors.
 *
 * @note The caller is responsible for freeing the returned string.
 */

/**
 * @brief Copies n bytes from src to dst.
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
 * @brief Appends n bytes from chunk to the growing buffer.
 *
 * Buffer metadata: meta[0] = capacity, meta[1] = current length.
 * When the buffer cannot hold the new data, its capacity is doubled
 * (repeatedly if necessary) to maintain amortized O(1) cost.
 *
 * @param buf   Pointer to buffer pointer (may be reallocated).
 * @param meta  meta[0]=capacity, meta[1]=length.
 * @param chunk Data to append.
 * @param n     Number of bytes to append.
 * @return 1 on success; 0 on malloc failure.
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
 * @brief Reads fd into buf until EOF. meta[0]=cap, meta[1]=len.
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
 * @brief Reads entire file into malloc'd string. Caller frees.
 * @return Allocated string or NULL on error
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
