/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:44:53 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_cone_bonus.c
 * @brief Ray–cone intersection: lateral mantle + circular base cap.
 *
 * A finite cone has its apex at center + axis×(height/2) and opens
 * downward along −axis.  The mantle satisfies a modified quadratic
 * (with m = 1 + (r/h)²).  After solving, each root is clipped to
 * the cone's height range [0, height] measured from the apex.  The
 * base cap is an additional disk intersection at the bottom.
 */

/**
 * @brief Solves the quadratic for the cone's lateral mantle.
 *
 * @param obj   Cone object (radius, height, axis).
 * @param ray   Ray to test.
 * @param apex  Pre-computed apex position.
 * @param roots Output: two roots of the quadratic.
 * @return 1 if real roots exist; 0 on negative discriminant or
 *         degenerate quadratic.
 */
static int	rt_solve_cone(t_obj *obj, t_ray ray, t_vec3 apex, double roots[2])
{
	t_vec3	co;
	double	v[2];
	double	abc[3];
	double	m;
	double	d;

	co = rt_sub(ray.orig, apex);
	v[0] = rt_dot(ray.dir, obj->axis);
	v[1] = rt_dot(co, obj->axis);
	m = 1.0 + (obj->radius / obj->height) * (obj->radius / obj->height);
	abc[0] = rt_dot(ray.dir, ray.dir) - m * v[0] * v[0];
	if (fabs(abc[0]) < EPS)
		return (0);
	abc[1] = 2.0 * (rt_dot(ray.dir, co) - m * v[0] * v[1]);
	abc[2] = rt_dot(co, co) - m * v[1] * v[1];
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0.0)
		return (0);
	roots[0] = (-abc[1] - sqrt(d)) / (2.0 * abc[0]);
	roots[1] = (-abc[1] + sqrt(d)) / (2.0 * abc[0]);
	return (1);
}

/**
 * @brief Picks the closest valid t for the cone side surface.
 *
 * A root is valid only if t > EPS and the axial projection of the
 * hit point falls within [0, height] from the apex.
 *
 * @param obj   Cone object.
 * @param ray   Ray.
 * @param apex  Pre-computed apex position.
 * @param roots Two quadratic roots.
 * @return Closest valid t, or 1e30 if both roots are rejected.
 */
static double	rt_pick_cone_side_t(t_obj *obj, t_ray ray, t_vec3 apex,
	double roots[2])
{
	t_vec3	q;
	double	t;
	double	h;
	int		i;

	t = 1e30;
	i = 0;
	while (i < 2)
	{
		if (roots[i] > EPS && roots[i] < t)
		{
			q = rt_add(rt_sub(ray.orig, apex), rt_scale(ray.dir, roots[i]));
			h = -rt_dot(q, obj->axis);
			if (h >= 0.0 && h <= obj->height)
				t = roots[i];
		}
		i++;
	}
	return (t);
}

/**
 * @brief Fills the hit record for a cone side intersection.
 *
 * The outward normal is derived from the cone geometry and flipped
 * if it faces away from the ray.  Material is applied via
 * rt_apply_hit_material.
 *
 * @param obj Object (cone).
 * @param ray Incoming ray.
 * @param t   Parameter at the hit.
 * @param hit Hit record to populate.
 */
static void	rt_set_cone_side_hit(t_obj *obj, t_ray ray, double t, t_hit *hit)
{
	t_vec3	apex;
	t_vec3	q;
	double	m;

	hit->hit = 1;
	hit->t = t;
	hit->point = rt_add(ray.orig, rt_scale(ray.dir, t));
	apex = rt_add(obj->center, rt_scale(obj->axis, obj->height * 0.5));
	q = rt_sub(hit->point, apex);
	m = 1.0 + (obj->radius / obj->height) * (obj->radius / obj->height);
	hit->normal = rt_sub(q, rt_scale(obj->axis, m * rt_dot(q, obj->axis)));
	hit->normal = rt_norm(hit->normal);
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
}

static int	rt_hit_cone_base(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_vec3	v[3];
	double	d[2];

	v[0] = rt_neg(obj->axis);
	d[0] = rt_dot(ray.dir, v[0]);
	if (fabs(d[0]) < EPS)
		return (0);
	v[1] = rt_add(obj->center, rt_scale(obj->axis, -obj->height * 0.5));
	d[1] = rt_dot(rt_sub(v[1], ray.orig), v[0]) / d[0];
	if (d[1] <= EPS || (hit->hit && d[1] >= hit->t))
		return (0);
	v[2] = rt_add(ray.orig, rt_scale(ray.dir, d[1]));
	if (rt_dot(rt_sub(v[2], v[1]), rt_sub(v[2], v[1]))
		> obj->radius * obj->radius + EPS)
		return (0);
	hit->hit = 1;
	hit->t = d[1];
	hit->point = v[2];
	hit->normal = v[0];
	if (rt_dot(hit->normal, ray.dir) > 0.0)
		hit->normal = rt_neg(hit->normal);
	rt_apply_hit_material(hit, obj);
	return (1);
}

/**
 * @brief Full cone intersection: side mantle ∪ base cap.
 *
 * Tests the lateral surface and the bottom-cap disk, then picks the
 * sub-hit with the smallest t.
 *
 * @param obj Object (cone).
 * @param ray Ray to test.
 * @param hit Output hit record.
 * @return 1 if any part of the cone was hit; 0 on complete miss.
 */
int	rt_hit_cone(t_obj *obj, t_ray ray, t_hit *hit)
{
	t_hit	out;
	t_vec3	apex;
	double	roots[2];
	double	t;

	out.hit = 0;
	out.t = 1e30;
	apex = rt_add(obj->center, rt_scale(obj->axis, obj->height * 0.5));
	if (rt_solve_cone(obj, ray, apex, roots))
	{
		t = rt_pick_cone_side_t(obj, ray, apex, roots);
		if (t != 1e30)
			rt_set_cone_side_hit(obj, ray, t, &out);
	}
	rt_hit_cone_base(obj, ray, &out);
	if (!out.hit)
		return (0);
	*hit = out;
	return (1);
}
