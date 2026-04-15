/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_plane_bonus.c
 * @brief Ray–plane intersection (bonus).
 *
 * Same N·D / N·(P0−O) formula as the mandatory version, but the hit
 * record also receives per-object material data via
 * rt_apply_hit_material.
 */

int	rt_hit_plane(t_obj *obj, t_ray ray, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	to_plane;

	denom = rt_dot(obj->axis, ray.dir);
	if (fabs(denom) < EPS)
		return (0);
	to_plane = rt_sub(obj->point, ray.orig);
	t = rt_dot(to_plane, obj->axis) / denom;
	if (t <= EPS)
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = rt_add(ray.orig, rt_scale(ray.dir, t));
	hit->normal = obj->axis;
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
	return (1);
}
