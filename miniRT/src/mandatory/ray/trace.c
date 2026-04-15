/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file trace.c
 * @brief Top-level ray tracing entry point.
 *
 * For each pixel the renderer casts a single primary ray.  This file
 * connects the hit test (rt_hit_scene) with the shading pass
 * (rt_shade_hit), returning black for rays that miss every object.
 */

/**
 * @brief Traces a primary ray through the scene.
 *
 * @param scene Scene containing objects and lights.
 * @param ray   Primary ray (origin + direction).
 * @return Shaded colour at the closest hit, or black (0,0,0) on miss.
 */
t_color	rt_trace_ray(t_scene *scene, t_ray ray)
{
	t_hit	hit;

	if (!rt_hit_scene(scene, ray, &hit))
		return (rt_color(0.0, 0.0, 0.0));
	return (rt_shade_hit(scene, &hit));
}
