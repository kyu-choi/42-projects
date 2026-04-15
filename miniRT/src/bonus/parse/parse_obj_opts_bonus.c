/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_opts_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_obj_opts_bonus.c
 * @brief Parses optional per-object suffixes: ck, sp, bm.
 *
 * After the mandatory colour field, an object line may contain zero or
 * more whitespace-separated option tokens:
 *   ck [scale]             — checker pattern (default scale = 1.0).
 *   sp specular shininess  — Phong specular (specular ∈ [0,1]).
 *   bm [scale [strength]]  — bump mapping (strength ∈ [0,2]).
 */

/**
 * @brief Parses the 'ck' (checker) option.
 *
 * Enables the checker flag and optionally reads a scale value.
 *
 * @param p   Cursor into the line (advanced).
 * @param obj Object to update.
 * @return 1 on success; 0 on parse error.
 */
static int	rt_parse_ck(char **p, t_obj *obj)
{
	char	c;

	obj->checker = 1;
	rt_skip_spaces(p);
	if (!**p)
		return (1);
	c = **p;
	if (c == '+' || c == '-' || c == '.' || ft_isdigit(c))
	{
		if (!rt_parse_double(p, &obj->checker_scale))
			return (0);
		if (obj->checker_scale <= EPS)
			return (0);
	}
	return (1);
}

/**
 * @brief Parses the 'sp' (specular) option.
 *
 * Reads two doubles: specular coefficient [0,1] and shininess (≥1).
 *
 * @param p   Cursor into the line (advanced).
 * @param obj Object to update.
 * @return 1 on success; 0 on parse error or out-of-range.
 */
static int	rt_parse_sp(char **p, t_obj *obj)
{
	rt_skip_spaces(p);
	if (!rt_parse_double(p, &obj->specular))
		return (0);
	rt_skip_spaces(p);
	if (!rt_parse_double(p, &obj->shininess))
		return (0);
	if (obj->specular < 0.0 || obj->specular > 1.0)
		return (0);
	if (obj->shininess < 1.0)
		return (0);
	return (1);
}

/**
 * @brief Parses the 'bm' (bump mapping) option.
 *
 * Enables bump and optionally reads scale and strength.
 * Strength is clamped to [0, 2].
 *
 * @param p   Cursor into the line (advanced).
 * @param obj Object to update.
 * @return 1 on success; 0 on parse error.
 */
static int	rt_parse_bm(char **p, t_obj *obj)
{
	char	c;

	obj->bump = 1;
	rt_skip_spaces(p);
	if (!**p)
		return (1);
	c = **p;
	if (c != '+' && c != '-' && c != '.' && !ft_isdigit(c))
		return (1);
	if (!rt_parse_double(p, &obj->bump_scale) || obj->bump_scale <= EPS)
		return (0);
	rt_skip_spaces(p);
	if (!**p)
		return (1);
	c = **p;
	if (c != '+' && c != '-' && c != '.' && !ft_isdigit(c))
		return (1);
	if (!rt_parse_double(p, &obj->bump_strength))
		return (0);
	return (obj->bump_strength >= 0.0 && obj->bump_strength <= 2.0);
}

static int	rt_parse_one_opt(char **p, t_obj *obj)
{
	if ((*p)[0] == 'c' && (*p)[1] == 'k' && ((*p)[2] == 0
		|| ft_isspace((*p)[2])))
	{
		*p = *p + 2;
		return (rt_parse_ck(p, obj));
	}
	if ((*p)[0] == 's' && (*p)[1] == 'p' && ((*p)[2] == 0
		|| ft_isspace((*p)[2])))
	{
		*p = *p + 2;
		return (rt_parse_sp(p, obj));
	}
	if ((*p)[0] == 'b' && (*p)[1] == 'm' && ((*p)[2] == 0
		|| ft_isspace((*p)[2])))
	{
		*p = *p + 2;
		return (rt_parse_bm(p, obj));
	}
	return (0);
}

int	rt_parse_obj_options(char **p, t_obj *obj)
{
	while (1)
	{
		rt_skip_spaces(p);
		if (!**p)
			return (1);
		if (!rt_parse_one_opt(p, obj))
			return (0);
	}
	return (1);
}
