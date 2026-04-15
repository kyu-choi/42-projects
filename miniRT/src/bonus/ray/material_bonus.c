/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file material_bonus.c
 * @brief Bump-mapping and per-object material application.
 *
 * After a ray–object intersection, this module perturbs the surface
 * normal via a procedural 3D sine/cosine gradient (bump mapping) and
 * copies checker-aware colour plus specular/shininess data into the
 * hit record.  This keeps material logic separate from intersection.
 */

/**
 * @brief Computes the object-local coordinate for bump sampling.
 *
 * Planes use `point` as origin, all others use `center`.
 *
 * @param obj   Object that was hit.
 * @param point World-space intersection point.
 * @return Local-space position vector.
 */
static t_vec3	rt_obj_local_point(t_obj *obj, t_vec3 point)
{
	if (obj->type == OBJ_PLANE)
		return (rt_sub(point, obj->point));
	return (rt_sub(point, obj->center));
}

/**
 * @brief Computes a procedural 3D bump gradient.
 *
 * Each component is a product of sin/cos applied to x, y, z scaled by
 * the bump_scale parameter.  This creates a smooth, tileable pattern
 * without any texture memory.
 *
 * @param p     Object-local position.
 * @param scale Frequency multiplier (higher = finer bumps).
 * @return Gradient vector (not normalised).
 */
static t_vec3	rt_bump_gradient(t_vec3 p, double scale)
{
	t_vec3	grad;

	grad.x = scale * cos(p.x * scale) * sin(p.y * scale) * sin(p.z * scale);
	grad.y = scale * sin(p.x * scale) * cos(p.y * scale) * sin(p.z * scale);
	grad.z = scale * sin(p.x * scale) * sin(p.y * scale) * cos(p.z * scale);
	return (grad);
}

/**
 * @brief Perturbs the surface normal using the bump gradient.
 *
 * The gradient's normal-parallel component is removed (Gram–Schmidt)
 * so the perturbation is tangential.  If the resulting vector is
 * near-zero (degenerate case), the original normal is returned.
 *
 * @param obj    Object (bump_scale, bump_strength fields).
 * @param point  World-space intersection point.
 * @param normal Original surface normal.
 * @return Perturbed (and normalised) surface normal.
 */
static t_vec3	rt_bump_normal(t_obj *obj, t_vec3 point, t_vec3 normal)
{
	t_vec3	local;
	t_vec3	grad;
	t_vec3	out;

	if (!obj->bump || obj->bump_strength <= EPS)
		return (normal);
	local = rt_obj_local_point(obj, point);
	grad = rt_bump_gradient(local, obj->bump_scale);
	grad = rt_sub(grad, rt_scale(normal, rt_dot(grad, normal)));
	out = rt_add(normal, rt_scale(grad, obj->bump_strength));
	if (rt_len(out) < EPS)
		return (normal);
	return (rt_norm(out));
}

/**
 * @brief Applies material to a hit record.
 *
 * Order: bump normal → checker/base colour → specular/shininess copy.
 *
 * @param hit Hit record to enrich.
 * @param obj Object that was intersected.
 */
void	rt_apply_hit_material(t_hit *hit, t_obj *obj)
{
	hit->normal = rt_bump_normal(obj, hit->point, hit->normal);
	hit->color = rt_get_object_color(obj, hit->point);
	hit->specular = obj->specular;
	hit->shininess = obj->shininess;
}
