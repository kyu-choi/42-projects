/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file parse_obj.c
 * @brief Parses geometric object lines: sp (sphere), pl (plane), cy
 *        (cylinder).
 *
 * Each parser allocates a t_obj, fills in its fields, and appends it to
 * the scene's linked list.  Diameter values from the .rt file are halved
 * to store as radius (internal representation is always radius).
 */

/**
 * @brief Frees obj and delegates to rt_error for message output.
 *
 * Used as an early-return helper so that every error path in a parser
 * can free the half-built object in a single expression.
 *
 * @param obj Object to free (may be partially initialised).
 * @param msg Error message forwarded to rt_error.
 * @return Always 0 (failure).
 */
static int	rt_free_obj_error(t_obj *obj, char *msg)
{
	free(obj);
	return (rt_error(msg));
}

/**
 * @brief Parses the four numeric fields of a cylinder line.
 *
 * Order: center(vec3) axis(norm_vec) diameter(double) height(double).
 * Diameter-to-radius conversion is done later by the caller.
 *
 * @param p   Cursor into the line (advanced past consumed tokens).
 * @param obj Cylinder object whose fields are filled in.
 * @return 1 on success; 0 if any field is invalid.
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
 * @brief Parses a sphere line: "sp center diameter R,G,B".
 *
 * Diameter is halved to store as radius.  Rejects non-positive diameter.
 *
 * @param s     Rest of line after "sp" identifier.
 * @param scene Scene to append the new sphere to.
 * @return 1 on success; 0 on error (malloc / format / range).
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
	if (!rt_parse_color(&p, &obj->color) || !rt_parse_end(p))
		return (rt_free_obj_error(obj, "Invalid sphere color"));
	obj->radius = obj->radius * 0.5;
	if (obj->radius <= 0.0)
		return (rt_free_obj_error(obj, "Sphere diameter must be positive"));
	return (rt_obj_add(scene, obj));
}

/**
 * @brief Parses a plane line: "pl point normal R,G,B".
 *
 * @param s     Rest of line after "pl" identifier.
 * @param scene Scene to append the new plane to.
 * @return 1 on success; 0 on error (malloc / format).
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
	if (!rt_parse_color(&p, &obj->color) || !rt_parse_end(p))
		return (rt_free_obj_error(obj, "Invalid plane color"));
	return (rt_obj_add(scene, obj));
}

/**
 * @brief Parses a cylinder line: "cy center axis diameter height R,G,B".
 *
 * Diameter is halved to store as radius.  Both radius and height must
 * be positive.
 *
 * @param s     Rest of line after "cy" identifier.
 * @param scene Scene to append the new cylinder to.
 * @return 1 on success; 0 on error (malloc / format / range).
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
	if (!rt_parse_color(&p, &obj->color) || !rt_parse_end(p))
		return (rt_free_obj_error(obj, "Invalid cylinder color"));
	obj->radius = obj->radius * 0.5;
	if (obj->radius <= 0.0 || obj->height <= 0.0)
		return (rt_free_obj_error(obj, "Cylinder size must be positive"));
	return (rt_obj_add(scene, obj));
}
