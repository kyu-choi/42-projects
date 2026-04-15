/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:30:33 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:50:27 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*t = c;
		t++;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	s1[12] = "restausrant";
	char	s = 'x';
	
	ft_memset(s1,s,5);
	printf("%s",s1);
	return (0);
}*/
