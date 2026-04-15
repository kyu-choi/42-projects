/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_paraboloid_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_paraboloid_bonus.c
 * @brief Ray–paraboloid intersection: lateral surface + open-end cap.
 *
 * A finite circular paraboloid with vertex at obj->center, opening
 * along obj->axis.  The opening radius at height h equals obj->radius.
 *
 * Surface equation (local coords):
 *   perp² = k * axial,  k = radius² / height
 * Bounded: 0 <= axial <= height.
 */

/**
 * @brief Solves the quadratic for the paraboloid surface.
 */
static int	rt_solve_parab(t_obj *obj, t_ray ray, double roots[2])
{
	t_vec3	oc;
	double	v[2];
	double	abc[3];
	double	k;
	double	d;

	oc = rt_sub(ray.orig, obj->center);
	v[0] = rt_dot(ray.dir, obj->axis);
	v[1] = rt_dot(oc, obj->axis);
	k = (obj->radius * obj->radius) / obj->height;
	abc[0] = rt_dot(ray.dir, ray.dir) - v[0] * v[0];
	if (fabs(abc[0]) < EPS)
		return (0);
	abc[1] = 2.0 * (rt_dot(ray.dir, oc) - v[0] * v[1]) - k * v[0];
	abc[2] = rt_dot(oc, oc) - v[1] * v[1] - k * v[1];
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0.0)
		return (0);
	roots[0] = (-abc[1] - sqrt(d)) / (2.0 * abc[0]);
	roots[1] = (-abc[1] + sqrt(d)) / (2.0 * abc[0]);
	return (1);
}

/**
 * @brief Picks the closest valid t on the paraboloid surface.
 */
static double	rt_pick_parab_t(t_obj *obj, t_ray ray, double roots[2])
{
	double	t;
	double	h;
	int		i;

	t = 1e30;
	i = 0;
	while (i < 2)
	{
		if (roots[i] > EPS && roots[i] < t)
		{
			h = rt_dot(rt_sub(rt_add(ray.orig, rt_scale(ray.dir, roots[i])),
						obj->center), obj->axis);
			if (h >= 0.0 && h <= obj->height)
				t = roots[i];
		}
		i++;
	}
	return (t);
}

/**
 * @brief Fills the hit record for a paraboloid surface hit.
 */
static void	rt_set_parab_hit(t_obj *obj, t_ray ray, double t, t_hit *hit)
{
	t_vec3	q;
	double	k;

	hit->hit = 1;
	hit->t = t;
	hit->point = rt_add(ray.orig, rt_scale(ray.dir, t));
	q = rt_sub(hit->point, obj->center);
	k = (obj->radius * obj->radius) / obj->height;
	hit->normal = rt_sub(rt_scale(q, 2.0),
			rt_scale(obj->axis, 2.0 * rt_dot(q, obj->axis) + k));
	hit->normal = rt_norm(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
}

/**
 * @brief Cap disk at the open end of the paraboloid.
 */
static int	rt_hit_parab_cap(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_vec3	cap;
	double	d[2];
	t_vec3	p;

	d[0] = rt_dot(ray.dir, obj->axis);
	if (fabs(d[0]) < EPS)
		return (0);
	cap = rt_add(obj->center, rt_scale(obj->axis, obj->height));
	d[1] = rt_dot(rt_sub(cap, ray.orig), obj->axis) / d[0];
	if (d[1] <= EPS || (hit->hit && d[1] >= hit->t))
		return (0);
	p = rt_add(ray.orig, rt_scale(ray.dir, d[1]));
	if (rt_dot(rt_sub(p, cap), rt_sub(p, cap))
		> obj->radius * obj->radius + EPS)
		return (0);
	hit->hit = 1;
	hit->t = d[1];
	hit->point = p;
	hit->normal = obj->axis;
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
	return (1);
}

/**
 * @brief Full paraboloid intersection: surface + cap.
 */
int	rt_hit_paraboloid(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_hit	out;
	double	roots[2];
	double	t;

	out.hit = 0;
	out.t = 1e30;
	if (rt_solve_parab(obj, ray, roots))
	{
		t = rt_pick_parab_t(obj, ray, roots);
		if (t != 1e30)
			rt_set_parab_hit(obj, ray, t, &out);
	}
	rt_hit_parab_cap(obj, ray, &out);
	if (!out.hit)
		return (0);
	*hit = out;
	return (1);
}
