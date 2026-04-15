/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_num_bonus.c
 * @brief Manual integer and double parsing from string (bonus).
 *
 * atof / strtod are not in the 42 allowed-function list, so numbers
 * are parsed character by character: sign → integer part → optional
 * fractional part.
 */

/**
 * @brief Consume optional +/-; return sign multiplier.
 * @param s Pointer to string; advanced past sign.
 * @return 1 or -1.
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

/**
 * @brief Parse optional fractional part (.digits); update value.
 * @param s Pointer to string; advanced.
 * @param value Accumulated value; fractional part added.
 * @param has_digit Set to 1 if any digit parsed.
 */
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

/**
 * @brief Parse integer from *s; advance *s.
 * @param s Pointer to string.
 * @param out Output value.
 * @return 1 on success; 0 if no valid integer.
 */
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

/**
 * @brief Parse double from *s; advance *s. Supports decimals.
 * @param s Pointer to string.
 * @param out Output value.
 * @return 1 on success; 0 if no valid number.
 */
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
