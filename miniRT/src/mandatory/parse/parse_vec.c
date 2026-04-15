/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file parse_vec.c
 * @brief Vector and color token parsers: "x,y,z" and "r,g,b".
 *
 * Format rules (from the subject PDF):
 * - vec3:   "x,y,z"     (doubles, comma-separated, no spaces)
 * - color:  "r,g,b"     (integers 0-255, comma-separated)
 * - normal: "x,y,z"     (doubles in [-1,1], then normalized)
 *
 * The parsers consume characters from *s and advance the pointer.
 * On failure *s is left at an undefined position (caller should
 * discard the line and report an error).
 */

/**
 * @brief Consumes single comma. Advances *s.
 */
static int	rt_parse_comma(char **s)
{
	if (**s != ',')
		return (0);
	(*s)++;
	return (1);
}

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
 * @brief Parses "r,g,b" (0-255 ints) into [0,1] float color.
 *
 * Each channel is validated to be in [0, 255] and then divided
 * by 255.0 to convert to the internal float representation.
 *
 * @param s Pointer to current parse position (advanced).
 * @param c Output color in [0,1] range.
 * @return 1 on success; 0 on format error or out-of-range.
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
 * @brief Parses a normalized direction vector.
 *
 * Each component must be in [-1, 1] per the subject specification.
 * After validation the vector is normalized to unit length.
 * Rejects zero-length vectors (|v| < EPS).
 *
 * @param s Pointer to current parse position (advanced).
 * @param v Output unit vector.
 * @return 1 on success; 0 on format, range, or zero-length error.
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
