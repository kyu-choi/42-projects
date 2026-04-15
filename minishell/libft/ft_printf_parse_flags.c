/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_flags.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:54:07 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Initializes the t_flags struct to its default values.
void	init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->specifier = 0;
}

// Parses simple flags: '-', '0', '#', ' ', '+'.
static void	parse_simple_flags(const char **format, t_flags *flags)
{
	while (ft_strchr("-0# +", **format))
	{
		if (**format == '-')
			flags->minus = 1;
		else if (**format == '0')
			flags->zero = 1;
		else if (**format == '#')
			flags->hash = 1;
		else if (**format == ' ')
			flags->space = 1;
		else if (**format == '+')
			flags->plus = 1;
		++(*format);
	}
}

// Parses only the width part.
static void	parse_width(const char **format, t_flags *flags, va_list ap)
{
	if (**format == '*')
	{
		flags->width = va_arg(ap, int);
		++(*format);
	}
	else if (ft_isdigit(**format))
	{
		flags->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			++(*format);
	}
}

// Parse only the precision part.
static void	parse_precision(const char **format, t_flags *flags, va_list ap)
{
	if (**format == '.')
	{
		++(*format);
		flags->precision = 0;
		if (**format == '*')
		{
			flags->precision = va_arg(ap, int);
			++(*format);
		}
		else if (ft_isdigit(**format))
		{
			flags->precision = ft_atoi(*format);
			while (ft_isdigit(**format))
				++(*format);
		}
	}
}

// Parses the entire format specifier part after '%' by calling helpers.
void	parse_format(const char **format, t_flags *flags, va_list ap)
{
	parse_simple_flags(format, flags);
	parse_width(format, flags, ap);
	parse_precision(format, flags, ap);
	if (ft_strchr("cspdiuxX%", **format))
	{
		flags->specifier = **format;
		++(*format);
	}
}
