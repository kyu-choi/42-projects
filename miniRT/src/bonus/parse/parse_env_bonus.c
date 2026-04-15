/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_env_bonus.c
 * @brief Parses environment elements: A (ambient), C (camera), L/l (lights).
 *
 * The bonus version extends light parsing:
 *   L — mandatory main light (must appear once; also added to list).
 *   l — extra bonus light (unlimited; appended to scene->lights).
 * A static helper rt_parse_light_value is shared by both L and l.
 */

/**
 * @brief Parse pos, ratio, optional color for a light.
 * @return 1 on success; 0 on error.
 */
static int	rt_parse_light_value(char *s, t_light *light)
{
	char	*p;

	p = s;
	light->color = rt_color(1.0, 1.0, 1.0);
	rt_skip_spaces(&p);
	if (!rt_parse_vec3(&p, &light->pos))
		return (rt_error("Invalid light position"));
	rt_skip_spaces(&p);
	if (!rt_parse_double(&p, &light->ratio))
		return (rt_error("Invalid light ratio"));
	rt_skip_spaces(&p);
	if (*p && !rt_parse_color(&p, &light->color))
		return (rt_error("Invalid light color"));
	if (!rt_parse_end(p) || light->ratio < 0.0 || light->ratio > 1.0)
		return (rt_error("Invalid light format"));
	return (1);
}

/**
 * @brief Parse 'A' line; ratio, color. Must appear once.
 * @return 1 on success; 0 on error/duplicate.
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
 * @brief Parse 'C' line; pos, dir, fov. Must appear once.
 * @return 1 on success; 0 on error/duplicate.
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
 * @brief Parse 'L' main light; add to lights list. Must appear once.
 * @return 1 on success; 0 on error/duplicate.
 */
int	rt_parse_light(char *s, t_scene *scene)
{
	t_light	light;

	if (scene->light.set)
		return (rt_error("Light duplicated"));
	light.set = 1;
	if (!rt_parse_light_value(s, &light))
		return (0);
	scene->light = light;
	if (!rt_light_add(scene, light))
		return (rt_error("Malloc failed"));
	return (1);
}

/**
 * @brief Parse 'l' extra light; add to lights list. Multi-light support.
 * @return 1 on success; 0 on error.
 */
int	rt_parse_light_extra(char *s, t_scene *scene)
{
	t_light	light;

	light.set = 1;
	if (!rt_parse_light_value(s, &light))
		return (0);
	if (!rt_light_add(scene, light))
		return (rt_error("Malloc failed"));
	return (1);
}
