/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_hyperboloid_bonus.c
 * @brief Ray–hyperboloid intersection: lateral surface + two caps.
 *
 * A finite one-sheet hyperboloid centred at obj->center with axis
 * obj->axis.  Waist radius is obj->radius; the surface flares
 * outward toward the caps at ±height/2.
 *
 * Surface equation (local coords):
 *   perp² - m * axial² = radius²
 * where m = 4 * radius² / height².
 */

/**
 * @brief Solves the quadratic for the hyperboloid surface.
 */
static int	rt_solve_hyper(t_obj *obj, t_ray ray, double roots[2])
{
	t_vec3	oc;
	double	v[2];
	double	abc[3];
	double	m;
	double	d;

	oc = rt_sub(ray.orig, obj->center);
	v[0] = rt_dot(ray.dir, obj->axis);
	v[1] = rt_dot(oc, obj->axis);
	m = 4.0 * (obj->radius * obj->radius) / (obj->height * obj->height);
	abc[0] = rt_dot(ray.dir, ray.dir) - (1.0 + m) * v[0] * v[0];
	if (fabs(abc[0]) < EPS)
		return (0);
	abc[1] = 2.0 * (rt_dot(ray.dir, oc) - (1.0 + m) * v[0] * v[1]);
	abc[2] = rt_dot(oc, oc) - (1.0 + m) * v[1] * v[1]
		- obj->radius * obj->radius;
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0.0)
		return (0);
	roots[0] = (-abc[1] - sqrt(d)) / (2.0 * abc[0]);
	roots[1] = (-abc[1] + sqrt(d)) / (2.0 * abc[0]);
	return (1);
}

/**
 * @brief Picks the closest valid t on the hyperboloid surface.
 */
static double	rt_pick_hyper_t(t_obj *obj, t_ray ray, double roots[2])
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
			if (h >= -obj->height * 0.5 && h <= obj->height * 0.5)
				t = roots[i];
		}
		i++;
	}
	return (t);
}

/**
 * @brief Fills the hit record for a hyperboloid side hit.
 */
static void	rt_set_hyper_hit(t_obj *obj, t_ray ray, double t, t_hit *hit)
{
	t_vec3	q;
	double	m;

	hit->hit = 1;
	hit->t = t;
	hit->point = rt_add(ray.orig, rt_scale(ray.dir, t));
	q = rt_sub(hit->point, obj->center);
	m = 4.0 * (obj->radius * obj->radius) / (obj->height * obj->height);
	hit->normal = rt_sub(q, rt_scale(obj->axis, (1.0 + m)
				* rt_dot(q, obj->axis)));
	hit->normal = rt_norm(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
}

/**
 * @brief Cap disk at offset h along axis.
 */
static int	rt_hit_hyper_cap(t_obj *obj, t_ray ray, double h, t_hit *hit)
{
	t_vec3	cap;
	double	d[2];
	t_vec3	p;

	d[0] = rt_dot(ray.dir, obj->axis);
	if (fabs(d[0]) < EPS)
		return (0);
	cap = rt_add(obj->center, rt_scale(obj->axis, h));
	d[1] = rt_dot(rt_sub(cap, ray.orig), obj->axis) / d[0];
	if (d[1] <= EPS || (hit->hit && d[1] >= hit->t))
		return (0);
	p = rt_add(ray.orig, rt_scale(ray.dir, d[1]));
	if (rt_dot(rt_sub(p, cap), rt_sub(p, cap))
		> obj->radius * obj->radius * 2.0 + EPS)
		return (0);
	hit->hit = 1;
	hit->t = d[1];
	hit->point = p;
	hit->normal = obj->axis;
	if (h < 0.0)
		hit->normal = rt_neg(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
	return (1);
}

/**
 * @brief Full hyperboloid intersection: side + two caps.
 */
int	rt_hit_hyperboloid(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_hit	out;
	double	roots[2];
	double	t;

	out.hit = 0;
	out.t = 1e30;
	if (rt_solve_hyper(obj, ray, roots))
	{
		t = rt_pick_hyper_t(obj, ray, roots);
		if (t != 1e30)
			rt_set_hyper_hit(obj, ray, t, &out);
	}
	rt_hit_hyper_cap(obj, ray, obj->height * 0.5, &out);
	rt_hit_hyper_cap(obj, ray, -obj->height * 0.5, &out);
	if (!out.hit)
		return (0);
	*hit = out;
	return (1);
}
