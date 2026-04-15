/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:27:01 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/02 16:27:51 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 32 || 126 < c)
		return (0);
	return (1);
}
/*
int	main(void)
{
	int	a;
	int	b;
	
	a = ft_isprint('<');
	printf("%d\n",a);
	b = ft_isprint('\t');
	printf("%d",b);
	return (0);
}*/
