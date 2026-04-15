/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:59:26 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:51:54 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	count;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	count = dstlen + srclen;
	if (dstlen >= size)
		return (size + srclen);
	i = 0;
	while ((i < size) && dst[i])
		i++;
	while ((i < size - 1) && *src)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	dst[i] = '\0';
	return (count);
}
