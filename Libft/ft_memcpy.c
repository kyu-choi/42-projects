/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:46:19 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:47:53 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*sor;

	if (!dest && !src)
		return (NULL);
	res = (unsigned char *)dest;
	sor = (unsigned char *)src;
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
	char	s1[10] = "";
	char	s2[10] = "apple";
	
	ft_memcpy(s1,s2,5);
	printf("%s",s1);
	return (0);
}*/
