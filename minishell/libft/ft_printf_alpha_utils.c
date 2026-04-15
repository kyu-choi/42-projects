/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_alpha_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:24:08 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_char_padding(int len, char c)
{
	int	count;

	if (len <= 0)
		return (0);
	count = 0;
	while (count < len)
	{
		if (write(1, &c, 1) != 1)
			return (-1);
		++count;
	}
	return (count);
}

int	apply_char_padding(char c, t_flags *flags)
{
	char	pad_char;
	int		pad_len;

	pad_len = 0;
	if (flags->width > 1)
		pad_len = flags->width - 1;
	pad_char = ' ';
	if (flags->zero && !flags->minus)
		pad_char = '0';
	if (flags->minus)
	{
		if (write(1, &c, 1) == -1
			|| print_char_padding(pad_len, pad_char) == -1)
			return (-1);
	}
	else
		if (print_char_padding(pad_len, pad_char) == -1
			|| write(1, &c, 1) == -1)
			return (-1);
	return (pad_len + 1);
}
