/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_obj_bonus.c
 * @brief Parses geometric object lines: sp, pl, cy (bonus).
 *
 * Same structure as the mandatory version, but each object line may
 * have optional suffixes (ck, sp, bm) parsed by rt_parse_obj_options.
 * Diameter values are halved to store as radius.
 */

/**
 * @brief Free obj and report error.
 * @return 0 always.
 */
static int	rt_free_obj_error(t_obj *obj, char *msg)
{
	free(obj);
	return (rt_error(msg));
}

/**
 * @brief Parse center, axis, radius, height for cylinder.
 * @return 1 on success; 0 on parse error.
 */
static int	rt_parse_cy_values(char **p, t_obj *obj)
{
	if (!rt_parse_vec3(p, &obj->center))
		return (0);
	rt_skip_spaces(p);
	if (!rt_parse_norm_vec(p, &obj->axis))
		return (0);
	rt_skip_spaces(p);
	if (!rt_parse_double(p, &obj->radius))
		return (0);
	rt_skip_spaces(p);
	if (!rt_parse_double(p, &obj->height))
		return (0);
	return (1);
}

/**
 * @brief Parse 'sp' line; diameter stored as radius.
 * @return 1 on success; 0 on error.
 */
int	rt_parse_sphere(char *s, t_scene *scene)
{
	char	*p;
	t_obj	*obj;

	obj = rt_obj_new(OBJ_SPHERE);
	if (!obj)
		return (rt_error("Malloc failed"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_vec3(&p, &obj->center))
		return (rt_free_obj_error(obj, "Invalid sphere center"));
	rt_skip_spaces(&p);
	if (!rt_parse_double(&p, &obj->radius))
		return (rt_free_obj_error(obj, "Invalid sphere diameter"));
	rt_skip_spaces(&p);
	if (!rt_parse_color(&p, &obj->color))
		return (rt_free_obj_error(obj, "Invalid sphere color"));
	if (!rt_parse_obj_options(&p, obj))
		return (rt_free_obj_error(obj, "Invalid sphere option"));
	obj->radius = obj->radius * 0.5;
	if (obj->radius <= 0.0)
		return (rt_free_obj_error(obj, "Sphere diameter must be positive"));
	return (rt_obj_add(scene, obj));
}

/**
 * @brief Parse 'pl' line; point, normal, color.
 * @return 1 on success; 0 on error.
 */
int	rt_parse_plane(char *s, t_scene *scene)
{
	char	*p;
	t_obj	*obj;

	obj = rt_obj_new(OBJ_PLANE);
	if (!obj)
		return (rt_error("Malloc failed"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_vec3(&p, &obj->point))
		return (rt_free_obj_error(obj, "Invalid plane point"));
	rt_skip_spaces(&p);
	if (!rt_parse_norm_vec(&p, &obj->axis))
		return (rt_free_obj_error(obj, "Invalid plane normal"));
	rt_skip_spaces(&p);
	if (!rt_parse_color(&p, &obj->color))
		return (rt_free_obj_error(obj, "Invalid plane color"));
	if (!rt_parse_obj_options(&p, obj))
		return (rt_free_obj_error(obj, "Invalid plane option"));
	return (rt_obj_add(scene, obj));
}

/**
 * @brief Parse 'cy' line; diameter stored as radius.
 * @return 1 on success; 0 on error.
 */
int	rt_parse_cylinder(char *s, t_scene *scene)
{
	char	*p;
	t_obj	*obj;

	obj = rt_obj_new(OBJ_CYLINDER);
	if (!obj)
		return (rt_error("Malloc failed"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_cy_values(&p, obj))
		return (rt_free_obj_error(obj, "Invalid cylinder values"));
	rt_skip_spaces(&p);
	if (!rt_parse_color(&p, &obj->color))
		return (rt_free_obj_error(obj, "Invalid cylinder color"));
	if (!rt_parse_obj_options(&p, obj))
		return (rt_free_obj_error(obj, "Invalid cylinder option"));
	obj->radius = obj->radius * 0.5;
	if (obj->radius <= 0.0 || obj->height <= 0.0)
		return (rt_free_obj_error(obj, "Cylinder size must be positive"));
	return (rt_obj_add(scene, obj));
}
