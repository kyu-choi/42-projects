/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:13:17 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/02 16:16:19 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	a;
	int	b;
	
	a = ft_isdigit('1');
	printf("%d\n",a);
	b = ft_isdigit('a');
	printf("%d",b);
	return (0);
}*/
