/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printunsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:17:12 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/05/11 18:17:18 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printunsigned(va_list args)
{
	int				count;
	unsigned int	num;
	char			*str;
	char			*a;

	count = 0;
	num = va_arg(args, unsigned int);
	str = utoa(num);
	a = str;
	while (*str)
	{
		write(1, str, 1);
		count++;
		str++;
	}
	free(a);
	return (count);
}
