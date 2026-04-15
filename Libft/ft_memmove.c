/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:00:59 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:49:39 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*res;
	unsigned char	*sor;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	res = (unsigned char *)dest;
	sor = (unsigned char *)src;
	if (res > sor)
	{
		while (n > 0)
		{
			res[n - 1] = sor[n - 1];
			n--;
		}
		return (dest);
	}
	i = 0;
	while (i < n)
	{
		res[i] = sor[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	s1[10] = "apple";
	
	ft_memmove(s1+2,s1,2);
	printf("%s",s1);
	return (0);
}*/
