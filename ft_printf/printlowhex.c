/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:17:43 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:17:55 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printlowhex(va_list args)
{
	int				count;
	unsigned int	num;
	char			*str;
	char			*a;

	count = 0;
	num = va_arg(args, unsigned int);
	str = utoa_lowhex(num);
	a = str;
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	free(a);
	return (count);
}
