/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:44:53 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_cone_bonus.c
 * @brief Parses the 'co' (cone) line from a .rt scene file.
 *
 * Format: co center axis diameter height R,G,B [opts]
 * Diameter is halved to store as radius.  Optional suffixes (ck, sp,
 * bm) are handled by rt_parse_obj_options.
 */

/**
 * @brief Frees a partially-built cone object and reports an error.
 *
 * @param obj Object to free.
 * @param msg Error message.
 * @return Always 0 (failure).
 */
static int	rt_free_cone_error(t_obj *obj, char *msg)
{
	free(obj);
	return (rt_error(msg));
}

/**
 * @brief Parses the four numeric fields of a cone line.
 *
 * Order: center(vec3) axis(norm_vec) diameter(double) height(double).
 *
 * @param p   Cursor into the line (advanced).
 * @param obj Cone object to fill.
 * @return 1 on success; 0 on parse error.
 */
static int	rt_parse_cone_values(char **p, t_obj *obj)
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
 * @brief Parses a complete 'co' cone line and appends to the scene.
 *
 * @param s     Rest of line after the 'co' identifier.
 * @param scene Scene to append the new cone to.
 * @return 1 on success; 0 on error (malloc / format / range).
 */
int	rt_parse_cone(char *s, t_scene *scene)
{
	char	*p;
	t_obj	*obj;

	obj = rt_obj_new(OBJ_CONE);
	if (!obj)
		return (rt_error("Malloc failed"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_cone_values(&p, obj))
		return (rt_free_cone_error(obj, "Invalid cone values"));
	rt_skip_spaces(&p);
	if (!rt_parse_color(&p, &obj->color))
		return (rt_free_cone_error(obj, "Invalid cone color"));
	if (!rt_parse_obj_options(&p, obj))
		return (rt_free_cone_error(obj, "Invalid cone option"));
	obj->radius = obj->radius * 0.5;
	if (obj->radius <= 0.0 || obj->height <= 0.0)
		return (rt_free_cone_error(obj, "Cone size must be positive"));
	return (rt_obj_add(scene, obj));
}
