/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle_padding.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:33:49 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Determines the padding character (' ' or '0').
// '0' flag is ignored if '-' is present, or if precision is set for numbers.
static char	get_pad_char(const t_flags *flags)
{
	if (flags->zero && !flags->minus)
	{
		if (ft_strchr("diuxX", flags->specifier) && flags->precision >= 0)
			return (' ');
		return ('0');
	}
	return (' ');
}

// Prints the padding characters to standard output.
static int	print_padding(int len, char c)
{
	char	*buffer;
	int		write_len;

	if (len <= 0)
		return (0);
	buffer = (char *)malloc(len);
	if (!buffer)
		return (-1);
	ft_memset(buffer, c, len);
	write_len = write(1, buffer, len);
	free(buffer);
	if (write_len != len)
		return (-1);
	return (write_len);
}

// Prints the formatted content with appropriate padding and handles memory.
// This is the final stage of the printing process.
int	print_with_padding(char *content, const t_flags *flags)
{
	int	content_len;
	int	pad_len;
	int	total_len;

	if (!content)
		return (-1);
	content_len = ft_strlen(content);
	pad_len = 0;
	if (flags->width > content_len)
		pad_len = flags->width - content_len;
	total_len = content_len + pad_len;
	if (flags->minus)
	{
		if (write(1, content, content_len) != (ssize_t)content_len
			|| print_padding(pad_len, ' ') == -1)
			total_len = -1;
	}
	else
	{
		if (print_padding(pad_len, get_pad_char(flags)) == -1
			|| write(1, content, content_len) != (ssize_t)content_len)
			total_len = -1;
	}
	return (free(content), total_len);
}
