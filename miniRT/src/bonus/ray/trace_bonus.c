/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file trace_bonus.c
 * @brief Ray tracing with depth-limited specular reflection.
 *
 * Extends the mandatory single-ray trace with recursive reflection
 * bounces (up to depth 2).  At each hit, if the surface has a
 * positive specular coefficient, a reflected ray is spawned and the
 * resulting colour is blended with the direct shading.
 */

/**
 * @brief Linearly blends base and reflected colour.
 *
 * result = (1 − ratio) × base + ratio × reflection, clamped.
 *
 * @param base  Direct shading colour.
 * @param refl  Colour from the reflected ray.
 * @param ratio Blend weight (== surface specular coefficient).
 * @return Blended and clamped colour.
 */
static t_color	rt_reflect_mix(t_color base, t_color refl, double ratio)
{
	t_color	out;
	double	keep;

	keep = 1.0 - ratio;
	out = rt_color_add(rt_color_mul(base, keep), rt_color_mul(refl, ratio));
	out.x = rt_clamp(out.x, 0.0, 1.0);
	out.y = rt_clamp(out.y, 0.0, 1.0);
	out.z = rt_clamp(out.z, 0.0, 1.0);
	return (out);
}

/**
 * @brief Recursive ray tracer with reflection.
 *
 * At each intersection: shade, then (if specular > 0 and depth > 0)
 * compute the mirror-reflection direction R = D − 2(D·N)N, offset
 * the origin by 2×EPS along the normal, and recurse.
 *
 * @param scene Scene data.
 * @param ray   Current ray.
 * @param depth Remaining reflection bounces (0 = no more).
 * @return Shaded colour for this ray path.
 */
static t_color	rt_trace_depth(t_scene *scene, t_ray ray, int depth)
{
	t_hit	hit;
	t_ray	refl;
	t_color	base;
	t_color	bounce;

	if (!rt_hit_scene(scene, ray, &hit))
		return (rt_color(0.0, 0.0, 0.0));
	base = rt_shade_hit(scene, &hit);
	if (depth <= 0 || hit.specular <= EPS)
		return (base);
	refl.orig = rt_add(hit.point, rt_scale(hit.normal, EPS * 2.0));
	refl.dir = rt_scale(hit.normal, 2.0 * rt_dot(ray.dir, hit.normal));
	refl.dir = rt_sub(ray.dir, refl.dir);
	refl.dir = rt_norm(refl.dir);
	bounce = rt_trace_depth(scene, refl, depth - 1);
	return (rt_reflect_mix(base, bounce, hit.specular));
}

/**
 * @brief Public entry point: traces a ray with up to 2 bounces.
 *
 * @param scene Scene data.
 * @param ray   Primary ray from the camera.
 * @return Final pixel colour (black on complete miss).
 */
t_color	rt_trace_ray(t_scene *scene, t_ray ray)
{
	return (rt_trace_depth(scene, ray, 2));
}
