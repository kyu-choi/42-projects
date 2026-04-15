/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hyperboloid_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file parse_hyperboloid_bonus.c
 * @brief Parses the 'hy' (hyperboloid) line from a .rt scene file.
 *
 * Format: hy center axis diameter height R,G,B [opts]
 * Diameter is halved to store as waist radius.
 */

static int	rt_free_hyper_error(t_obj *obj, char *msg)
{
	free(obj);
	return (rt_error(msg));
}

static int	rt_parse_hyper_values(char **p, t_obj *obj)
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
 * @brief Parses a complete 'hy' hyperboloid line.
 */
int	rt_parse_hyperboloid(char *s, t_scene *scene)
{
	char	*p;
	t_obj	*obj;

	obj = rt_obj_new(OBJ_HYPERBOLOID);
	if (!obj)
		return (rt_error("Malloc failed"));
	p = s;
	rt_skip_spaces(&p);
	if (!rt_parse_hyper_values(&p, obj))
		return (rt_free_hyper_error(obj, "Invalid hyperboloid values"));
	rt_skip_spaces(&p);
	if (!rt_parse_color(&p, &obj->color))
		return (rt_free_hyper_error(obj, "Invalid hyperboloid color"));
	if (!rt_parse_obj_options(&p, obj))
		return (rt_free_hyper_error(obj, "Invalid hyperboloid option"));
	obj->radius = obj->radius * 0.5;
	if (obj->radius <= 0.0 || obj->height <= 0.0)
		return (rt_free_hyper_error(obj, "Hyperboloid size must be > 0"));
	return (rt_obj_add(scene, obj));
}
