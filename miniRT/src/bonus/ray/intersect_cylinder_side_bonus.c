/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_side_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_cylinder_side_bonus.c
 * @brief Ray–cylinder lateral surface intersection (bonus).
 *
 * Same quadratic derivation as the mandatory version, but the hit
 * record also receives per-object material data (checker, specular,
 * bump) via rt_apply_hit_material.
 */

static int	rt_solve_quadratic(double a, double b, double c, double roots[2])
{
	double	d;

	if (fabs(a) < EPS)
		return (0);
	d = b * b - 4.0 * a * c;
	if (d < 0.0)
		return (0);
	roots[0] = (-b - sqrt(d)) / (2.0 * a);
	roots[1] = (-b + sqrt(d)) / (2.0 * a);
	return (1);
}

static double	rt_pick_side_t(t_obj *obj, double v[2], double roots[2])
{
	double	t;

	t = 1e30;
	if (roots[0] > EPS && fabs(v[1] + roots[0] * v[0]) <= obj->height * 0.5)
		t = roots[0];
	if (roots[1] > EPS && roots[1] < t
		&& fabs(v[1] + roots[1] * v[0]) <= obj->height * 0.5)
		t = roots[1];
	return (t);
}

static void	rt_prepare_side(t_obj *obj, t_ray ray, t_vec3 v3[3], double v[5])
{
	v3[0] = rt_sub(ray.orig, obj->center);
	v[0] = rt_dot(ray.dir, obj->axis);
	v[1] = rt_dot(v3[0], obj->axis);
	v3[1] = rt_sub(ray.dir, rt_scale(obj->axis, v[0]));
	v3[2] = rt_sub(v3[0], rt_scale(obj->axis, v[1]));
	v[2] = rt_dot(v3[1], v3[1]);
	v[3] = 2.0 * rt_dot(v3[1], v3[2]);
	v[4] = rt_dot(v3[2], v3[2]) - obj->radius * obj->radius;
}

static void	rt_set_side_hit(t_obj *obj, t_ray ray, double t, t_hit *hit)
{
	t_vec3	tmp;

	hit->hit = 1;
	hit->t = t;
	hit->point = rt_add(ray.orig, rt_scale(ray.dir, t));
	tmp = rt_sub(hit->point, obj->center);
	hit->normal = rt_sub(tmp, rt_scale(obj->axis, rt_dot(tmp, obj->axis)));
	hit->normal = rt_norm(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
}

int	rt_hit_cylinder_side(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_vec3	v3[3];
	double	v[5];
	double	roots[2];

	rt_prepare_side(obj, ray, v3, v);
	if (!rt_solve_quadratic(v[2], v[3], v[4], roots))
		return (0);
	v[4] = rt_pick_side_t(obj, v, roots);
	if (v[4] == 1e30)
		return (0);
	rt_set_side_hit(obj, ray, v[4], hit);
	return (1);
}
