/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers_numeric.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:33:46 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Static helper to apply precision (leading zeros) to a number string.
static char	*apply_precision(char *num_str, t_flags *flags)
{
	char	*padding;
	char	*new_str;
	int		num_len;
	int		pad_len;

	if (!num_str)
		return (NULL);
	num_len = ft_strlen(num_str);
	if (flags->precision <= num_len)
		return (num_str);
	pad_len = flags->precision - num_len;
	padding = (char *)malloc(pad_len + 1);
	if (!padding)
		return (free(num_str), NULL);
	ft_memset(padding, '0', pad_len);
	padding[pad_len] = '\0';
	new_str = ft_strjoin(padding, num_str);
	return (free(padding), free(num_str), new_str);
}

static int	print_numeric_content(char *content, const char *prefix,
				t_flags *flags)
{
	char	*final_str;
	int		ret;
	size_t	prefix_len;

	if (!content)
		return (-1);
	prefix_len = ft_strlen(prefix);
	if (flags->zero && !flags->minus && flags->precision < 0)
	{
		flags->width -= prefix_len;
		if (prefix_len > 0)
			if (write(1, prefix, prefix_len) != (ssize_t)prefix_len)
				return (free(content), -1);
		ret = print_with_padding(content, flags);
		if (ret == -1)
			return (-1);
		return (ret + prefix_len);
	}
	final_str = ft_strjoin(prefix, content);
	free(content);
	if (!final_str)
		return (-1);
	return (print_with_padding(final_str, flags));
}

// Handles 'd' (decimal) and 'i' (integer) specifiers.
int	handle_decimal(t_flags *flags, va_list ap)
{
	long long	num;
	char		*content;
	char		*prefix;

	num = va_arg(ap, int);
	prefix = "";
	if (num < 0)
	{
		prefix = "-";
		num *= -1;
	}
	else if (flags->plus)
		prefix = "+";
	else if (flags->space)
		prefix = " ";
	if (flags->precision == 0 && num == 0)
		content = ft_strdup("");
	else
		content = ft_uitoa((unsigned int)num);
	if (!content)
		return (-1);
	content = apply_precision(content, flags);
	return (print_numeric_content(content, prefix, flags));
}

// Handles 'u' (unsigned decimal) specifier.
int	handle_unsigned(t_flags *flags, va_list ap)
{
	unsigned int	num;
	char			*content;

	num = va_arg(ap, unsigned int);
	if (flags->precision == 0 && num == 0)
		content = ft_strdup("");
	else
		content = ft_uitoa(num);
	if (!content)
		return (-1);
	content = apply_precision(content, flags);
	return (print_numeric_content(content, "", flags));
}

// Handles 'x' and 'X' (hexadecimal) specifiers.
int	handle_hex(t_flags *flags, va_list ap)
{
	unsigned int	num;
	char			*content;
	char			*prefix;

	num = va_arg(ap, unsigned int);
	prefix = "";
	if (flags->hash && num != 0)
	{
		if (flags->specifier == 'x')
			prefix = "0x";
		else
			prefix = "0X";
	}
	if (flags->precision == 0 && num == 0)
		content = ft_strdup("");
	else
		content = ft_ultoa_hex(num, flags->specifier);
	if (!content)
		return (-1);
	content = apply_precision(content, flags);
	return (print_numeric_content(content, prefix, flags));
}
