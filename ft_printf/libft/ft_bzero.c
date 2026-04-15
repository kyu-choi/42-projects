/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:29 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:47:29 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*t = 0;
		t++;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char	s1[7] = "abcdef";
	
	ft_bzero(&s1[3],3);
	printf("%s",s1);
	return (0);
}
*/
