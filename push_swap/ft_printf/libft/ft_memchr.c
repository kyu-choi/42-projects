/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:08:46 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/04 16:31:47 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*res;

	res = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*res == (unsigned char)c)
			return ((void *)res);
		res++;
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello, world!";
	char	find = 'w';
	void	*res;
	
	res = ft_memchr(str, find, sizeof(str));
	
	
	
}*/
