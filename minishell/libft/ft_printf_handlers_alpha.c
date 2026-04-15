/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers_alpha.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:33:46 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Handles '%' (percent sign) specifier.
// The project tester expects flags (width, -, 0) to be ignored or '%%'.
int	handle_percent(t_flags *flags)
{
	if (IS_LINUX)
		return (handle_percent_linux(flags));
	return (handle_percent_macos(flags));
}

// Handles 'c' (char) specifier.
// Creates a 1-character string to be passed to the padding function.
int	handle_char(t_flags *flags, va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	return (apply_char_padding(c, flags));
}

// Handles 's' (string) specifier.
// Applies precision by truncating the string if needed.
int	handle_string(t_flags *flags, va_list ap)
{
	char	*str_in;
	char	*str_out;
	char	*content;
	size_t	len;

	str_in = va_arg(ap, char *);
	if (IS_LINUX)
		str_out = get_processed_string_and_len_linux(str_in, flags, &len);
	else
		str_out = get_processed_string_and_len_macos(str_in, flags, &len);
	content = ft_substr(str_out, 0, len);
	if (!content)
		return (-1);
	return (print_with_padding(content, flags));
}

// Handles 'p' (pointer) specifier.
// Prepends "0x" and handles the (nil) case for a NULL pointer.
int	handle_pointer(t_flags *flags, va_list ap)
{
	unsigned long	ptr_val;
	char			*hex_str;
	char			*content;

	ptr_val = (unsigned long)va_arg(ap, void *);
	if (ptr_val == 0)
	{
		content = ft_strdup(PRINT_NULL_AS_0X0);
		if (!content)
			return (-1);
	}
	else
	{
		hex_str = ft_ultoa_hex(ptr_val, 'x');
		if (!hex_str)
			return (-1);
		content = ft_strjoin("0x", hex_str);
		free(hex_str);
		if (!content)
			return (-1);
	}
	return (print_with_padding(content, flags));
}
