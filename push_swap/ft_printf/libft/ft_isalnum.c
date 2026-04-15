/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:16:40 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/02 16:21:38 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((47 < c && c < 58) || (64 < c && c < 91) || (96 < c && c < 123))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	a;
	int	b;
	
	a = ft_isalnum('a');
	printf("%d\n",a);
	
	b = ft_isalnum('?');
	printf("%d\n",b);
	return (0);
}*/
