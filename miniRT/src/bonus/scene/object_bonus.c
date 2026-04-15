/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file object_bonus.c
 * @brief Object allocation (with bonus defaults) and list management.
 *
 * The bonus version initialises additional fields: checker, specular,
 * bump, and their associated parameters.  The linked-list append logic
 * is identical to the mandatory version.
 */

/**
 * @brief Return last node of object list.
 */
static t_obj	*rt_obj_last(t_obj *obj)
{
	while (obj && obj->next)
		obj = obj->next;
	return (obj);
}

/**
 * @brief Allocate obj with bonus defaults (checker, bump, specular).
 * @param type OBJ_SPHERE/PLANE/CYLINDER/CONE.
 * @return New object or NULL.
 */
t_obj	*rt_obj_new(int type)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->center = rt_vec3(0.0, 0.0, 0.0);
	obj->axis = rt_vec3(0.0, 1.0, 0.0);
	obj->point = rt_vec3(0.0, 0.0, 0.0);
	obj->radius = 0.0;
	obj->height = 0.0;
	obj->color = rt_color(1.0, 1.0, 1.0);
	obj->checker = 0;
	obj->checker_scale = 1.0;
	obj->checker_color = rt_color(1.0, 1.0, 1.0);
	obj->specular = 0.35;
	obj->shininess = 48.0;
	obj->bump = 0;
	obj->bump_scale = 8.0;
	obj->bump_strength = 0.2;
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Append obj to scene->objs.
 * @return 1 on success; 0 if scene or obj NULL.
 */
int	rt_obj_add(t_scene *scene, t_obj *obj)
{
	t_obj	*last;

	if (!scene || !obj)
		return (0);
	if (!scene->objs)
		scene->objs = obj;
	else
	{
		last = rt_obj_last(scene->objs);
		last->next = obj;
	}
	return (1);
}
