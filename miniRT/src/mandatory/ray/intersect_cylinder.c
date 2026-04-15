/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file intersect_cylinder.c
 * @brief Complete cylinder intersection: lateral surface + two caps.
 *
 * A finite cylinder is the union of its lateral surface and its two
 * flat circular caps.  This file tests all three sub-surfaces and
 * returns the nearest hit.  Caps are tested as disk–ray intersections:
 * intersect the cap plane, then reject if the hit point lies outside
 * the cap radius.
 */

/**
 * @brief Sets the cap hit normal (points towards the ray origin).
 *
 * @param obj Object whose axis defines the cap orientation.
 * @param ray Incoming ray (used to flip the normal towards the viewer).
 * @param h   Signed offset along axis; sign selects top/bottom cap.
 * @param hit Hit record to update (normal + colour).
 */
static void	rt_set_cap_hit(t_obj *obj, t_ray ray, double h, t_hit *hit)
{
	hit->normal = obj->axis;
	if (h < 0.0)
		hit->normal = rt_neg(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	hit->color = obj->color;
}

/**
 * @brief Tests a ray against one circular cap at height h along axis.
 *
 * @param obj Object (cylinder) with center, axis, radius.
 * @param ray Ray to test.
 * @param h   Signed half-height offset (±height/2).
 * @param hit Hit record updated only if this cap is closer.
 * @return 1 if hit; 0 if miss (parallel, behind, outside disk, or
 *         farther than current hit).
 */
static int	rt_hit_one_cap(t_obj *obj, t_ray ray, double h, t_hit *hit)
{
	t_vec3	cap;
	t_vec3	p;
	t_vec3	radial;
	double	t;
	double	denom;

	denom = rt_dot(ray.dir, obj->axis);
	if (fabs(denom) < EPS)
		return (0);
	cap = rt_add(obj->center, rt_scale(obj->axis, h));
	t = rt_dot(rt_sub(cap, ray.orig), obj->axis) / denom;
	if (t <= EPS || (hit->hit && t >= hit->t))
		return (0);
	p = rt_add(ray.orig, rt_scale(ray.dir, t));
	radial = rt_sub(p, cap);
	if (rt_dot(radial, radial) > obj->radius * obj->radius + EPS)
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = p;
	rt_set_cap_hit(obj, ray, h, hit);
	return (1);
}

/**
 * @brief Tests both caps and returns the closest valid cap hit.
 *
 * @param obj Object (cylinder).
 * @param ray Ray to test.
 * @param hit Hit record updated if a cap is hit.
 * @return 1 if at least one cap was hit; 0 otherwise.
 */
static int	rt_hit_cy_caps(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_hit	cap_hit;
	int		found;

	cap_hit.hit = 0;
	cap_hit.t = 1e30;
	found = 0;
	if (rt_hit_one_cap(obj, ray, obj->height * 0.5, &cap_hit))
		found = 1;
	if (rt_hit_one_cap(obj, ray, -obj->height * 0.5, &cap_hit))
		found = 1;
	if (!found)
		return (0);
	*hit = cap_hit;
	return (1);
}

/**
 * @brief Helper: copies a hit record (side or cap) into the output.
 *
 * @param dst Destination hit record.
 * @param src Source hit record.
 * @return Always 1 (success).
 */
static int	rt_set_hit(t_hit *dst, t_hit *src)
{
	*dst = *src;
	return (1);
}

/**
 * @brief Full cylinder intersection: side ∪ top cap ∪ bottom cap.
 *
 * Tests the lateral surface and both caps independently, then picks
 * the sub-hit with the smallest t.
 *
 * @param obj Object (cylinder).
 * @param ray Ray to test.
 * @param hit Output hit record.
 * @return 1 if any part of the cylinder was hit; 0 on complete miss.
 */
int	rt_hit_cylinder(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_hit	side;
	t_hit	caps;
	int		has_side;
	int		has_caps;

	has_side = rt_hit_cylinder_side(obj, ray, &side);
	has_caps = rt_hit_cy_caps(obj, ray, &caps);
	if (has_side && has_caps && side.t < caps.t)
		return (rt_set_hit(hit, &side));
	if (has_side && has_caps)
		return (rt_set_hit(hit, &caps));
	if (has_side)
		return (rt_set_hit(hit, &side));
	if (has_caps)
		return (rt_set_hit(hit, &caps));
	return (0);
}
