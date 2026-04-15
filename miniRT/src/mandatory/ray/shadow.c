/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file shadow.c
 * @brief Shadow-ray test for point-light occlusion.
 *
 * A shadow ray is cast from the hit point towards the light source.
 * The origin is offset along the surface normal by 2×EPS to prevent
 * self-intersection (shadow acne).  If any object intersects between
 * the offset origin and the light, the point is considered shadowed.
 */

/**
 * @brief Tests whether point p is in shadow.
 *
 * Algorithm:
 *   1. Offset origin along normal n by 2×EPS.
 *   2. Compute direction and distance to the light.
 *   3. Cast ray; if nearest hit < dist, point is occluded.
 *
 * @param scene Scene with objects and light position.
 * @param p     Surface intersection point.
 * @param n     Surface normal at p (used for offset direction).
 * @return 1 if in shadow; 0 if lit.
 */
int	rt_in_shadow(t_scene *scene, t_vec3 p, t_vec3 n)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	to_light;
	double	dist;

	ray.orig = rt_add(p, rt_scale(n, EPS * 2.0));
	to_light = rt_sub(scene->light.pos, ray.orig);
	dist = rt_len(to_light);
	ray.dir = rt_norm(to_light);
	if (rt_hit_scene(scene, ray, &hit) && hit.t < dist - EPS)
		return (1);
	return (0);
}
