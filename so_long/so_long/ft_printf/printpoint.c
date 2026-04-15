/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:16:37 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:16:43 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printpoint(va_list args)
{
	int					count;
	void				*ptr;
	unsigned long long	num;
	char				*str;
	char				*tmp;

	ptr = va_arg(args, void *);
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = 0;
	num = (unsigned long long)ptr;
	str = lltoa_hex(num);
	tmp = str;
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	free(tmp);
	return (count);
}
