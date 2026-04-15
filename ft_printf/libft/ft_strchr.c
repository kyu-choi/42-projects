/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:49:39 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/06 15:51:16 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	*res;

	res = (unsigned char *)str;
	while (*res)
	{
		if (*res == (unsigned char)c)
			return ((char *)res);
		res++;
	}
	if (*res == (unsigned char)c)
		return ((char *)res);
	return (NULL);
}
/*
int	main(void)
{
	char	*s1 = "choikyuchan";
	char	a = 'k';
	char	*s2;
	
	s2 = ft_strchr(s1, a);
	printf("%s",s2);
	return (0);
}*/
