/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file object.c
 * @brief Object allocation and singly-linked list management.
 *
 * Every geometric primitive in the scene is stored as a t_obj node.
 * New nodes are appended to the tail so that rendering order matches
 * the file order, which simplifies TAB-cycling in the interactive
 * controls.
 */

/**
 * @brief Returns the last node of the object linked list.
 *
 * @param obj Head of the list (may be NULL).
 * @return Pointer to the tail node, or NULL if list is empty.
 */
static t_obj	*rt_obj_last(t_obj *obj)
{
	while (obj && obj->next)
		obj = obj->next;
	return (obj);
}

/**
 * @brief Allocates a t_obj and sets safe defaults.
 *
 * All numeric fields are zeroed / given neutral values so that a
 * partially-filled object does not contain garbage.
 *
 * @param type Object type (OBJ_SPHERE, OBJ_PLANE, OBJ_CYLINDER).
 * @return Pointer to the new object, or NULL on malloc failure.
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
	obj->next = NULL;
	return (obj);
}

/**
 * @brief Appends an object to the scene's linked list.
 *
 * @param scene Target scene (must not be NULL).
 * @param obj   Object to append (must not be NULL).
 * @return 1 on success; 0 if scene or obj is NULL.
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
