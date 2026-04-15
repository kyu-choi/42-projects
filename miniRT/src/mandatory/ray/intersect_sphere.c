/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file intersect_sphere.c
 * @brief Ray–sphere intersection using the analytic quadratic method.
 *
 * Given ray P(t) = O + tD and sphere |P − C|² = r², substitution
 * yields a quadratic at² + bt + c = 0 where
 *   a = D·D,  b = 2(OC·D),  c = OC·OC − r²,  OC = O − C.
 * The discriminant determines 0 / 1 / 2 real roots.  The smallest
 * positive root (t > EPS) is the visible intersection.
 */

static int	rt_pick_root(double a, double b, double c, double *t)
{
	double	d;
	double	roots[2];

	d = b * b - 4.0 * a * c;
	if (d < 0.0)
		return (0);
	roots[0] = (-b - sqrt(d)) / (2.0 * a);
	roots[1] = (-b + sqrt(d)) / (2.0 * a);
	*t = 1e30;
	if (roots[0] > EPS && roots[0] < *t)
		*t = roots[0];
	if (roots[1] > EPS && roots[1] < *t)
		*t = roots[1];
	if (*t == 1e30)
		return (0);
	return (1);
}

int	rt_hit_sphere(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_vec3	oc;
	double	abc[3];
	double	t;

	oc = rt_sub(ray.orig, obj->center);
	abc[0] = rt_dot(ray.dir, ray.dir);
	abc[1] = 2.0 * rt_dot(oc, ray.dir);
	abc[2] = rt_dot(oc, oc) - obj->radius * obj->radius;
	if (!rt_pick_root(abc[0], abc[1], abc[2], &t))
		return (0);
	hit->hit = 1;
	hit->t = t;
	hit->point = rt_add(ray.orig, rt_scale(ray.dir, t));
	hit->normal = rt_norm(rt_sub(hit->point, obj->center));
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	hit->color = obj->color;
	return (1);
}
