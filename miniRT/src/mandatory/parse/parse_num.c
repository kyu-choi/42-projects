/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file parse_num.c
 * @brief Numeric token parsers: integer and floating-point.
 *
 * Parsing strategy (without using atof/strtod):
 * 1. Optional sign (+/-)
 * 2. Integer part: accumulate digits (value = value*10 + digit)
 * 3. Optional fractional part: after '.', accumulate with
 *    decreasing base (0.1, 0.01, ...)
 *
 * Both parsers advance the source pointer past consumed characters
 * and set a has_digit flag so that strings like "." or "+" are
 * correctly rejected as invalid numbers.
 *
 * @note atof/strtod are NOT in the allowed function list; hence
 *       we implement manual parsing.
 */

static int	rt_parse_sign(char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

static void	rt_parse_frac(char **s, double *value, int *has_digit)
{
	double	base;

	base = 0.1;
	if (**s != '.')
		return ;
	(*s)++;
	while (ft_isdigit(**s))
	{
		*value = *value + (base * (double)(**s - '0'));
		base = base * 0.1;
		(*s)++;
		*has_digit = 1;
	}
}

int	rt_parse_int(char **s, int *out)
{
	int	sign;
	int	value;
	int	has_digit;

	sign = rt_parse_sign(s);
	value = 0;
	has_digit = 0;
	while (ft_isdigit(**s))
	{
		value = value * 10 + (**s - '0');
		(*s)++;
		has_digit = 1;
	}
	if (!has_digit)
		return (0);
	*out = value * sign;
	return (1);
}

int	rt_parse_double(char **s, double *out)
{
	int		sign;
	double	value;
	int		has_digit;

	sign = rt_parse_sign(s);
	value = 0.0;
	has_digit = 0;
	while (ft_isdigit(**s))
	{
		value = value * 10.0 + (double)(**s - '0');
		(*s)++;
		has_digit = 1;
	}
	rt_parse_frac(s, &value, &has_digit);
	if (!has_digit)
		return (0);
	*out = value * (double)sign;
	return (1);
}
