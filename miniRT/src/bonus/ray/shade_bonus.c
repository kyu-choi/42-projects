/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file shade_bonus.c
 * @brief Full Phong shading: ambient + per-light (diffuse + specular).
 *
 * Unlike the mandatory version (single light, diffuse only), the bonus
 * shader iterates every light in scene->lights and adds a Blinn–Phong
 * specular highlight when the hit surface has specular > 0.
 */

/**
 * @brief Computes the ambient lighting term.
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
 * @brief Lambertian diffuse contribution from a single light.
 *
 * @param hit   Hit record (normal, colour).
 * @param ldir  Unit vector from hit point to light.
 * @param light Light source.
 * @return Diffuse colour term.
 */
static t_color	rt_diffuse_term(t_hit *hit, t_vec3 ldir, t_light *light)
{
	double	ndotl;
	t_color	c;

	ndotl = rt_dot(hit->normal, ldir);
	if (ndotl < 0.0)
		ndotl = 0.0;
	c = rt_color_mod(hit->color, light->color);
	c = rt_color_mul(c, ndotl * light->ratio);
	return (c);
}

/**
 * @brief Phong specular highlight from a single light.
 *
 * Uses the reflection vector R = 2(N·L)N − L.  The exponent
 * (shininess) controls highlight tightness.
 *
 * @param scene Scene (camera position for view vector).
 * @param hit   Hit record (point, normal, specular, shininess).
 * @param ldir  Unit vector from hit point to light.
 * @param light Light source.
 * @return Specular colour term, or black if specular ≤ 0.
 */
static t_color	rt_specular_term(t_scene *scene, t_hit *hit,
	t_vec3 ldir, t_light *light)
{
	t_vec3	view;
	t_vec3	refl;
	double	spec;

	if (hit->specular <= 0.0)
		return (rt_color(0.0, 0.0, 0.0));
	view = rt_norm(rt_sub(scene->cam.pos, hit->point));
	refl = rt_scale(hit->normal, 2.0 * rt_dot(hit->normal, ldir));
	refl = rt_norm(rt_sub(refl, ldir));
	spec = rt_dot(view, refl);
	if (spec < 0.0)
		spec = 0.0;
	spec = pow(spec, hit->shininess) * hit->specular;
	return (rt_color_mul(light->color, spec * light->ratio));
}

/**
 * @brief Combined diffuse + specular from one light (0 if shadowed).
 *
 * @param scene Scene with objects (for shadow test).
 * @param hit   Hit record.
 * @param light Light to evaluate.
 * @return Colour contribution from this light, or black if occluded.
 */
static t_color	rt_light_term(t_scene *scene, t_hit *hit, t_light *light)
{
	t_vec3	ldir;
	t_color	diff;
	t_color	spec;

	if (rt_in_shadow_light(scene, hit->point, hit->normal, light))
		return (rt_color(0.0, 0.0, 0.0));
	ldir = rt_norm(rt_sub(light->pos, hit->point));
	diff = rt_diffuse_term(hit, ldir, light);
	spec = rt_specular_term(scene, hit, ldir, light);
	return (rt_color_add(diff, spec));
}

/**
 * @brief Full shading: ambient + Σ(lights) (diffuse + specular).
 *
 * Iterates the multi-light linked list.  Each channel is clamped to
 * [0, 1] to prevent over-bright pixels.
 *
 * @param scene Scene with lighting data and object list.
 * @param hit   Hit record for the intersection point.
 * @return Final pixel colour (each channel in [0, 1]).
 */
t_color	rt_shade_hit(t_scene *scene, t_hit *hit)
{
	t_color			out;
	t_light_node	*node;

	out = rt_ambient_term(scene, hit);
	node = scene->lights;
	while (node)
	{
		out = rt_color_add(out, rt_light_term(scene, hit, &node->light));
		node = node->next;
	}
	out.x = rt_clamp(out.x, 0.0, 1.0);
	out.y = rt_clamp(out.y, 0.0, 1.0);
	out.z = rt_clamp(out.z, 0.0, 1.0);
	return (out);
}
