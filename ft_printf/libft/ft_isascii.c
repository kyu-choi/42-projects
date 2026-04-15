/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:22:19 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/02 16:24:56 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c < 128)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	a;
	int	b;
	
	a = ft_isascii(5);
	printf("%d\n",a);
	
	b = ft_isascii(-1);
	printf("%d\n",b);
	return (0);
}*/
