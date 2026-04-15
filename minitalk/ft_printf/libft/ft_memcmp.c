/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:32:29 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:02 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	if (!s1 && !s2)
		return (0);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	int	a;
	int	b;
	
	char	*s1 = "apple";
	char	*s2 = "apple";
	char	*s3 = "appue";
	
	a = ft_memcmp(s1,s2,4);
	printf("%d\n",a);
	b = ft_memcmp(s2,s3,5);
	printf("%d",b);
	return (0);
}*/
