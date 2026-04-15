/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_cylinder_bonus.c
 * @brief Complete cylinder intersection: side + two caps (bonus).
 *
 * Tests lateral surface and both circular caps, returns the nearest
 * hit.  Material is applied via rt_apply_hit_material.
 */

/**
 * @brief Set cap hit normal (axis direction) and material.
 */
static void	rt_set_cap_hit(t_obj *obj, t_ray ray, double h, t_hit *hit)
{
	hit->normal = obj->axis;
	if (h < 0.0)
		hit->normal = rt_neg(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
}

/**
 * @brief Ray-cap intersection at offset h along axis.
 * @return 1 if hit and closer than current; 0 otherwise.
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
 * @brief Try both caps; return closest hit.
 * @return 1 if any cap hit; 0 otherwise.
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
 * @brief Copy src hit to dst; return 1.
 */
static int	rt_set_hit(t_hit *dst, t_hit *src)
{
	*dst = *src;
	return (1);
}

/**
 * @brief Ray-cylinder: side + caps; return closest hit.
 * @return 1 if hit; 0 otherwise.
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
