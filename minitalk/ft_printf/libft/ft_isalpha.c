/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:01:34 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/02 16:13:02 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((64 < c && c < 91) || (96 < c && c < 123))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	a;
	int	b;
	
	a = ft_isalpha('a');
	printf("%d\n",a);
	b = ft_isalpha('3');
	printf("%d",b);
	return (0);
}*/
