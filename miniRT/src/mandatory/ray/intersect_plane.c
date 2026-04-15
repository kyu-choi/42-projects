/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file intersect_plane.c
 * @brief Ray–plane intersection.
 *
 * A plane is defined by a point P0 and a normal N.  For ray
 * P(t) = O + tD, the intersection satisfies N·(P(t) − P0) = 0,
 * giving t = N·(P0 − O) / (N·D).  The ray is parallel (miss) when
 * |N·D| < EPS, and behind the camera when t ≤ EPS.
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
	hit->color = obj->color;
	return (1);
}
