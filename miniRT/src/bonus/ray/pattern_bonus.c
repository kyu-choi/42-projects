/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file pattern_bonus.c
 * @brief Checker-board pattern for all object types.
 *
 * Planes use a tangent-space UV projection (two orthogonal axes on the
 * plane surface).  Spheres, cylinders, and cones use a volume-based
 * 3D checker (floor of each world-axis coordinate).
 */

/**
 * @brief Picks a world-up hint vector for the plane UV basis.
 *
 * If the plane normal is nearly parallel to Y, X is used instead to
 * avoid a degenerate cross product.
 *
 * @param n Plane normal.
 * @return A vector guaranteed not to be parallel to n.
 */
static t_vec3	rt_checker_basis(t_vec3 n)
{
	if (fabs(n.y) < 0.95)
		return (rt_vec3(0.0, 1.0, 0.0));
	return (rt_vec3(1.0, 0.0, 0.0));
}

/**
 * @brief Checker cell index for a plane surface.
 *
 * Projects the hit point onto the plane's local U/V axes and floors
 * each coordinate.  The sum of the two floor values determines
 * even/odd (checker cell).
 *
 * @param obj   Plane object (point, axis, checker_scale).
 * @param point World-space hit point.
 * @return 1 if alternate-colour cell; 0 for base colour.
 */
static int	rt_checker_plane(t_obj *obj, t_vec3 point)
{
	t_vec3	base;
	t_vec3	u;
	t_vec3	p;
	int		cell;
	double	v;

	base = rt_checker_basis(obj->axis);
	u = rt_norm(rt_cross(obj->axis, base));
	p = rt_sub(point, obj->point);
	cell = (int)floor(rt_dot(p, u) * obj->checker_scale);
	v = floor(rt_dot(p, rt_cross(obj->axis, u)) * obj->checker_scale);
	cell = cell + (int)v;
	if (cell % 2)
		return (1);
	return (0);
}

/**
 * @brief Checker cell for volumetric objects (sphere/cylinder/cone).
 *
 * Uses the 3D floor of (x, y, z) relative to the object centre.
 *
 * @param obj   Object (center, checker_scale).
 * @param point World-space hit point.
 * @return 1 if alternate-colour cell; 0 for base colour.
 */
static int	rt_checker_volume(t_obj *obj, t_vec3 point)
{
	t_vec3	p;
	int		cell;

	p = rt_sub(point, obj->center);
	cell = (int)floor(p.x * obj->checker_scale);
	cell = cell + (int)floor(p.y * obj->checker_scale);
	cell = cell + (int)floor(p.z * obj->checker_scale);
	if (cell % 2)
		return (1);
	return (0);
}

/**
 * @brief Dispatches checker evaluation by object type.
 *
 * @param obj   Object to evaluate.
 * @param point World-space hit point.
 * @return 1 if alternate-colour cell; 0 for base colour.
 */
static int	rt_checker_pick(t_obj *obj, t_vec3 point)
{
	if (obj->type == OBJ_PLANE)
		return (rt_checker_plane(obj, point));
	return (rt_checker_volume(obj, point));
}

/**
 * @brief Returns the surface colour at a given point.
 *
 * If the object has a checker pattern enabled, the colour alternates
 * between obj->color and obj->checker_color.  Otherwise the base
 * colour is returned directly.
 *
 * @param obj   Object to query.
 * @param point World-space hit point.
 * @return Colour in [0, 1] range.
 */
t_color	rt_get_object_color(t_obj *obj, t_vec3 point)
{
	if (!obj->checker)
		return (obj->color);
	if (rt_checker_pick(obj, point))
		return (obj->checker_color);
	return (obj->color);
}
