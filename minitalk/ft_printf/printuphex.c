/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printHEX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:18:03 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:18:10 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printuphex(va_list args)
{
	int				count;
	unsigned int	num;
	char			*str;
	char			*a;

	count = 0;
	num = va_arg(args, unsigned int);
	str = utoa_uphex(num);
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
