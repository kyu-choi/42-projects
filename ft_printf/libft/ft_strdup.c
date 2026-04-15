/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:38:25 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/02 20:43:24 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		count;
	char	*res;

	count = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(void)
{
	char	*s1 = "banana";
	char	*s2;
	
	s2 = ft_strdup(s1);
	printf("%s",s2);
	return (0);
}*/
