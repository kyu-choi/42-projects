/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_scene_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file intersect_scene_bonus.c
 * @brief Scene-wide ray intersection: closest hit (bonus).
 *
 * Iterates all objects, dispatching to sphere / plane / cylinder /
 * cone handlers.  Keeps the hit with the smallest positive t.
 */

/**
 * @brief Hit test by type (sphere, plane, cylinder, cone).
 * @return 1 if hit; 0 otherwise.
 */
static int	rt_hit_object(t_obj *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		return (rt_hit_sphere(obj, ray, hit));
	if (obj->type == OBJ_PLANE)
		return (rt_hit_plane(obj, ray, hit));
	if (obj->type == OBJ_CYLINDER)
		return (rt_hit_cylinder(obj, ray, hit));
	if (obj->type == OBJ_CONE)
		return (rt_hit_cone(obj, ray, hit));
	if (obj->type == OBJ_HYPERBOLOID)
		return (rt_hit_hyperboloid(obj, ray, hit));
	if (obj->type == OBJ_PARABOLOID)
		return (rt_hit_paraboloid(obj, ray, hit));
	return (0);
}

/**
 * @brief Find closest hit among all scene objects.
 * @return 1 if any hit; 0 otherwise. hit has closest.
 */
int	rt_hit_scene(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_obj	*obj;
	t_hit	tmp;
	int		found;

	obj = scene->objs;
	found = 0;
	hit->hit = 0;
	hit->t = 1e30;
	while (obj)
	{
		if (rt_hit_object(obj, ray, &tmp) && tmp.t < hit->t)
		{
			*hit = tmp;
			found = 1;
		}
		obj = obj->next;
	}
	return (found);
}
