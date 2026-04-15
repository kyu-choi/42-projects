/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file shade.c
 * @brief Phong-like shading: ambient + Lambertian diffuse.
 *
 * The mandatory target uses a simplified lighting model:
 *   final = ambient_term + diffuse_term
 * where ambient = obj_color * amb_color * amb_ratio,
 * and diffuse = max(N·L, 0) * light_ratio * obj_color (if not in
 * shadow).  Each channel is clamped to [0, 1] before pixel output.
 */

/**
 * @brief Computes the ambient lighting term.
 *
 * ambient = object_color ⊗ ambient_color × ambient_ratio.
 * The ⊗ is per-channel multiplication (color modulate).
 *
 * @param scene Scene with ambient light settings.
 * @param hit   Hit record containing the surface colour.
 * @return Ambient colour contribution.
 */
static t_color	rt_ambient_term(t_scene *scene, t_hit *hit)
{
	t_color	c;

	c = rt_color_mod(hit->color, scene->amb.color);
	c = rt_color_mul(c, scene->amb.ratio);
	return (c);
}

/**
 * @brief Computes the Lambertian diffuse term.
 *
 * diffuse = max(N·L, 0) × light_ratio × object_color.
 * Returns black immediately if the hit point is in shadow (no need
 * to compute the dot product).
 *
 * @param scene Scene with light position and ratio.
 * @param hit   Hit record (point, normal, colour).
 * @return Diffuse colour contribution, or black if shadowed.
 */
static t_color	rt_diffuse_term(t_scene *scene, t_hit *hit)
{
	t_vec3	ldir;
	double	ndotl;
	t_color	c;

	if (rt_in_shadow(scene, hit->point, hit->normal))
		return (rt_color(0.0, 0.0, 0.0));
	ldir = rt_norm(rt_sub(scene->light.pos, hit->point));
	ndotl = rt_dot(hit->normal, ldir);
	if (ndotl < 0.0)
		ndotl = 0.0;
	c = rt_color_mul(hit->color, ndotl * scene->light.ratio);
	return (c);
}

/**
 * @brief Combines ambient and diffuse terms, clamped to [0, 1].
 *
 * @param scene Scene with lighting data.
 * @param hit   Hit record for the intersection point.
 * @return Final pixel colour (each channel in [0, 1]).
 */
t_color	rt_shade_hit(t_scene *scene, t_hit *hit)
{
	t_color	out;
	t_color	amb;
	t_color	diff;

	amb = rt_ambient_term(scene, hit);
	diff = rt_diffuse_term(scene, hit);
	out = rt_color_add(amb, diff);
	out.x = rt_clamp(out.x, 0.0, 1.0);
	out.y = rt_clamp(out.y, 0.0, 1.0);
	out.z = rt_clamp(out.z, 0.0, 1.0);
	return (out);
}
