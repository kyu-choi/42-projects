/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file parse_env.c
 * @brief Parsers for scene environment elements: A, C, L.
 *
 * Each element appears exactly once per scene file:
 * - A: Ambient light   (ratio [0,1], color)
 * - C: Camera           (position, direction, FOV)
 * - L: Point light      (position, brightness [0,1], optional color)
 *
 * Duplicate detection: scene->amb.set / cam.set / light.set flags
 * are checked before parsing to enforce the "exactly once" rule.
 */

/**
 * @brief Parses ambient line: "A ratio r,g,b".
 *
 * @param s     Rest of line after identifier.
 * @param scene Scene to update (amb.set, amb.ratio, amb.color).
 * @return 1 on success; 0 on error (duplicate/format/range).
 *
 * @note ratio must be in [0.0, 1.0].
 */
int	rt_parse_ambient(char *s, t_scene *scene)
{
	char	*p;
	double	ratio;
	t_color	color;

	if (scene->amb.set)
		return (rt_error("Ambient duplicated"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_double(&p, &ratio))
		return (rt_error("Invalid ambient ratio"));
	rt_skip_spaces(&p);
	if (!rt_parse_color(&p, &color) || !rt_parse_end(p))
		return (rt_error("Invalid ambient color"));
	if (ratio < 0.0 || ratio > 1.0)
		return (rt_error("Ambient ratio out of range"));
	scene->amb.set = 1;
	scene->amb.ratio = ratio;
	scene->amb.color = color;
	return (1);
}

/**
 * @brief Parses camera line: "C pos dir fov".
 *
 * @param s     Rest of line after identifier.
 * @param scene Scene to update (cam fields).
 * @return 1 on success; 0 on error (duplicate/format/range).
 *
 * @note dir must be a normalized vector; fov must be in (0, 180).
 */
int	rt_parse_camera(char *s, t_scene *scene)
{
	char	*p;
	t_vec3	pos;
	t_vec3	dir;
	double	fov;

	if (scene->cam.set)
		return (rt_error("Camera duplicated"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_vec3(&p, &pos))
		return (rt_error("Invalid camera position"));
	rt_skip_spaces(&p);
	if (!rt_parse_norm_vec(&p, &dir))
		return (rt_error("Invalid camera direction"));
	rt_skip_spaces(&p);
	if (!rt_parse_double(&p, &fov) || !rt_parse_end(p))
		return (rt_error("Invalid camera fov"));
	if (fov <= 0.0 || fov >= 180.0)
		return (rt_error("Camera fov out of range"));
	scene->cam.set = 1;
	scene->cam.pos = pos;
	scene->cam.dir = dir;
	scene->cam.fov = fov;
	return (1);
}

/**
 * @brief Parses light line: "L pos ratio [r,g,b]".
 *
 * The color field is optional; defaults to white (1,1,1) if absent.
 *
 * @param s     Rest of line after identifier.
 * @param scene Scene to update (light fields).
 * @return 1 on success; 0 on error (duplicate/format/range).
 *
 * @note ratio must be in [0.0, 1.0].
 */
int	rt_parse_light(char *s, t_scene *scene)
{
	char	*p;
	t_vec3	pos;
	double	ratio;
	t_color	color;

	if (scene->light.set)
		return (rt_error("Light duplicated"));
	p = s;
	color = rt_color(1.0, 1.0, 1.0);
	rt_skip_spaces(&p);
	if (!rt_parse_vec3(&p, &pos))
		return (rt_error("Invalid light position"));
	rt_skip_spaces(&p);
	if (!rt_parse_double(&p, &ratio))
		return (rt_error("Invalid light ratio"));
	rt_skip_spaces(&p);
	if (*p && !rt_parse_color(&p, &color))
		return (rt_error("Invalid light color"));
	if (!rt_parse_end(p) || ratio < 0.0 || ratio > 1.0)
		return (rt_error("Invalid light format"));
	scene->light.set = 1;
	scene->light.pos = pos;
	scene->light.ratio = ratio;
	scene->light.color = color;
	return (1);
}
