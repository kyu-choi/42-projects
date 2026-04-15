/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file intersect_scene.c
 * @brief Scene-wide ray intersection: finds the closest hit.
 *
 * Iterates the object linked list, dispatches to the per-type
 * intersection routine, and keeps the hit record with the smallest
 * positive t.  Used both for primary rays and shadow rays.
 */

/**
 * @brief Dispatches a ray test to the correct per-type handler.
 *
 * @param obj Object to test (sphere / plane / cylinder).
 * @param ray Ray to intersect.
 * @param hit Output hit record (filled only on success).
 * @return 1 if hit; 0 if miss.
 */
static int	rt_hit_object(t_obj *obj, t_ray ray, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		return (rt_hit_sphere(obj, ray, hit));
	if (obj->type == OBJ_PLANE)
		return (rt_hit_plane(obj, ray, hit));
	if (obj->type == OBJ_CYLINDER)
		return (rt_hit_cylinder(obj, ray, hit));
	return (0);
}

/**
 * @brief Finds the closest intersection among all objects.
 *
 * Initialises hit->t to 1e30 (infinity sentinel) and walks the list.
 * Each per-type test that returns a smaller t overwrites the record.
 *
 * @param scene Scene containing the object list.
 * @param ray   Ray to test against every object.
 * @param hit   Output: closest hit record.
 * @return 1 if any object was hit; 0 if ray misses everything.
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
