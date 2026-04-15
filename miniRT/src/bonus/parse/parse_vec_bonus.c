/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_vec_bonus.c
 * @brief Parse compound vector types: vec3, colour (0-255), normal.
 *
 * Format rules (from the 42 subject PDF):
 *   vec3:       x,y,z      (no spaces around commas).
 *   colour:     R,G,B      each in [0, 255] → stored as [0, 1].
 *   norm_vec:   x,y,z      each in [-1, 1], then normalised.
 */

/**
 * @brief Consume comma; advance *s.
 * @return 1 if comma found; 0 otherwise.
 */
static int	rt_parse_comma(char **s)
{
	if (**s != ',')
		return (0);
	(*s)++;
	return (1);
}

/**
 * @brief Parse "x,y,z" into v; advance *s.
 * @return 1 on success; 0 on parse error.
 */
int	rt_parse_vec3(char **s, t_vec3 *v)
{
	if (!rt_parse_double(s, &v->x))
		return (0);
	if (!rt_parse_comma(s))
		return (0);
	if (!rt_parse_double(s, &v->y))
		return (0);
	if (!rt_parse_comma(s))
		return (0);
	if (!rt_parse_double(s, &v->z))
		return (0);
	return (1);
}

/**
 * @brief Parse "r,g,b" (0-255); store as 0-1 in c.
 * @return 1 on success; 0 on parse/range error.
 */
int	rt_parse_color(char **s, t_color *c)
{
	int	r;
	int	g;
	int	b;

	if (!rt_parse_int(s, &r) || !rt_parse_comma(s))
		return (0);
	if (!rt_parse_int(s, &g) || !rt_parse_comma(s))
		return (0);
	if (!rt_parse_int(s, &b))
		return (0);
	if (r < 0 || r > 255 || g < 0 || g > 255)
		return (0);
	if (b < 0 || b > 255)
		return (0);
	*c = rt_color((double)r / 255.0, (double)g / 255.0, (double)b / 255.0);
	return (1);
}

/**
 * @brief Parse vec3, ensure [-1,1] range, normalize.
 * @return 1 on success; 0 on parse/zero-length error.
 */
int	rt_parse_norm_vec(char **s, t_vec3 *v)
{
	double	len;

	if (!rt_parse_vec3(s, v))
		return (0);
	if (v->x < -1.0 || v->x > 1.0)
		return (0);
	if (v->y < -1.0 || v->y > 1.0)
		return (0);
	if (v->z < -1.0 || v->z > 1.0)
		return (0);
	len = rt_len(*v);
	if (len < EPS)
		return (0);
	*v = rt_norm(*v);
	return (1);
}
