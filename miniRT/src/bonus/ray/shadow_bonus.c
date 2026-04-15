/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file shadow_bonus.c
 * @brief Per-light shadow ray test (bonus multi-light support).
 *
 * Unlike the mandatory single-light version, this file provides
 * rt_in_shadow_light which accepts an arbitrary light pointer, so the
 * shader can test occlusion for every light in the linked list.
 */

/**
 * @brief Tests whether a point is in shadow for a specific light.
 *
 * Shadow ray origin is offset along the surface normal by 2×EPS to
 * prevent self-intersection.  If any object intersects between the
 * origin and the light, the point is considered shadowed.
 *
 * @param scene Scene with objects.
 * @param p     Surface intersection point.
 * @param n     Surface normal at p.
 * @param light Light source to test occlusion against.
 * @return 1 if in shadow; 0 if lit.
 */
int	rt_in_shadow_light(t_scene *scene, t_vec3 p, t_vec3 n, t_light *light)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	to_light;
	double	dist;

	ray.orig = rt_add(p, rt_scale(n, EPS * 2.0));
	to_light = rt_sub(light->pos, ray.orig);
	dist = rt_len(to_light);
	ray.dir = rt_norm(to_light);
	if (rt_hit_scene(scene, ray, &hit) && hit.t < dist - EPS)
		return (1);
	return (0);
}

/**
 * @brief Convenience wrapper: shadow test against the scene's main light.
 *
 * @param scene Scene with the default light field.
 * @param p     Surface intersection point.
 * @param n     Surface normal at p.
 * @return 1 if in shadow; 0 if lit.
 */
int	rt_in_shadow(t_scene *scene, t_vec3 p, t_vec3 n)
{
	return (rt_in_shadow_light(scene, p, n, &scene->light));
}
