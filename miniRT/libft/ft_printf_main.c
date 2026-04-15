/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:07 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Handles the entire conversion process when a '%' is encountered.
// 1. Initialize flags.
// 2. Parse flags, width, and precision.
// 3. Dispatch and print according to the specifier.
static int	process_conversion(const char **format, va_list ap)
{
	t_flags	flags;

	init_flags(&flags);
	parse_format(format, &flags, ap);
	if (flags.specifier)
		return (dispatch_print(&flags, ap));
	return (0);
}

// Process one segment of the format strin within the main loop.
// Handles either a conversion specifier or a literal character.
// Return -1 on write error, 0 otherwise.
static int	handle_format_loop(const char **format, va_list ap, int *total_len)
{
	int	write_len;

	if (**format == '%')
	{
		++(*format);
		write_len = process_conversion(format, ap);
		if (write_len == -1)
			return (-1);
		*total_len += write_len;
	}
	else
	{
		if (write(1, *format, 1) == -1)
			return (-1);
		++(*total_len);
		++(*format);
	}
	return (0);
}

// Main ft_printf function
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		total_len;

	if (!format)
		return (-1);
	total_len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (handle_format_loop(&format, ap, &total_len) == -1)
		{
			total_len = -1;
			break ;
		}
	}
	va_end(ap);
	return (total_len);
}
