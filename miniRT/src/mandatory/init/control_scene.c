/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:34:59 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file control_scene.c
 * @brief Light translation and object manipulation controls.
 *
 * This module handles all scene-element changes triggered by keys:
 * - TAB: cycle selected object through the linked list
 * - IJKLUO: translate the light along X/Y/Z axes
 * - FBRTYG: translate the selected object along X/Y/Z axes
 * - ZXCV: rotate the selected object's axis (yaw/pitch)
 * - +/-: resize radius; N/M: resize cylinder height
 *
 * @note Planes use obj->point instead of obj->center for position.
 * @note Spheres ignore rotation (axis has no visual effect).
 */

/**
 * @brief Translate light position along world axes.
 *
 * Axis mapping: J/L = X, U/O = Y, I/K = Z.
 * Step size is STEP_MOVE (0.8) units per key press.
 *
 * @param rt  Runtime context (scene.light.pos modified).
 * @param key Key code to test.
 * @return 1 if key matched; 0 otherwise.
 */
static int	rt_move_light(t_rt *rt, int key)
{
	if (key == KEY_J)
		rt->scene.light.pos.x -= STEP_MOVE;
	else if (key == KEY_L)
		rt->scene.light.pos.x += STEP_MOVE;
	else if (key == KEY_U)
		rt->scene.light.pos.y += STEP_MOVE;
	else if (key == KEY_O)
		rt->scene.light.pos.y -= STEP_MOVE;
	else if (key == KEY_I)
		rt->scene.light.pos.z += STEP_MOVE;
	else if (key == KEY_K)
		rt->scene.light.pos.z -= STEP_MOVE;
	else
		return (0);
	return (1);
}

/**
 * @brief Translate selected object along world axes.
 *
 * For planes the reference point is obj->point (not center),
 * because a plane is defined by a point on its surface + normal.
 * Axis mapping: F/B = X, R/Y = Y, T/G = Z.
 *
 * @param rt  Runtime context.
 * @param key Key code to test.
 * @return 1 if key matched and object exists; 0 otherwise.
 */
static int	rt_move_object(t_rt *rt, int key)
{
	t_vec3	*target;
	t_obj	*obj;

	obj = rt->selected_obj;
	if (!obj)
		return (0);
	target = &obj->center;
	if (obj->type == OBJ_PLANE)
		target = &obj->point;
	if (key == KEY_F)
		target->x -= STEP_MOVE;
	else if (key == KEY_B)
		target->x += STEP_MOVE;
	else if (key == KEY_R)
		target->y += STEP_MOVE;
	else if (key == KEY_Y)
		target->y -= STEP_MOVE;
	else if (key == KEY_T)
		target->z += STEP_MOVE;
	else if (key == KEY_G)
		target->z -= STEP_MOVE;
	else
		return (0);
	return (1);
}

/**
 * @brief Rotate selected object's axis vector.
 *
 * Z/X: yaw (rotate around world-Y)
 * C/V: pitch (rotate around world-X)
 * Spheres are ignored because rotating a sphere has no visible effect.
 * After rotation the axis is re-normalized.
 *
 * @param rt  Runtime context.
 * @param key Key code to test.
 * @return 1 if rotated; 0 if sphere, no selection, or unbound key.
 */
static int	rt_rotate_object(t_rt *rt, int key)
{
	t_obj	*obj;
	t_vec3	axis;
	double	angle;

	obj = rt->selected_obj;
	if (!obj || obj->type == OBJ_SPHERE)
		return (0);
	if (key != KEY_Z && key != KEY_X && key != KEY_C && key != KEY_V)
		return (0);
	axis = rt_vec3(0.0, 1.0, 0.0);
	angle = STEP_ROT;
	if (key == KEY_X || key == KEY_V)
		angle = -STEP_ROT;
	if (key == KEY_C || key == KEY_V)
		axis = rt_vec3(1.0, 0.0, 0.0);
	obj->axis = rt_rotate_axis(obj->axis, axis, angle);
	obj->axis = rt_norm(obj->axis);
	return (1);
}

/**
 * @brief Resize selected object: +/- radius, N/M cylinder height.
 *
 * Radius minimum is STEP_SIZE to prevent zero/negative values.
 * Height resize only applies to cylinders (plane/sphere ignored).
 *
 * @param rt  Runtime context.
 * @param key Key code to test.
 * @return 1 if resized; 0 otherwise.
 */
static int	rt_resize_object(t_rt *rt, int key)
{
	t_obj	*obj;

	obj = rt->selected_obj;
	if (!obj)
		return (0);
	if ((key == KEY_PLUS || key == KEY_MINUS) && obj->type != OBJ_PLANE)
	{
		if (key == KEY_PLUS)
			obj->radius += STEP_SIZE;
		else
			obj->radius = rt_clamp(obj->radius - STEP_SIZE, STEP_SIZE, 1e9);
		return (1);
	}
	if (obj->type == OBJ_CYLINDER && (key == KEY_N || key == KEY_M))
	{
		if (key == KEY_N)
			obj->height += STEP_SIZE;
		else
			obj->height = rt_clamp(obj->height - STEP_SIZE, STEP_SIZE, 1e9);
		return (1);
	}
	return (0);
}

/**
 * @brief Dispatches scene controls: TAB select, light, move,
 *        rotate, resize.
 *
 * TAB cycles through the object linked list; wraps to head when
 * the end is reached. This gives the user a way to select any
 * object without a mouse.
 *
 * @param rt  Runtime context.
 * @param key Key code to test.
 * @return 1 if any scene key was handled; 0 otherwise.
 */
int	rt_control_scene(t_rt *rt, int key)
{
	if (key == KEY_TAB && rt->scene.objs)
	{
		if (!rt->selected_obj || !rt->selected_obj->next)
			rt->selected_obj = rt->scene.objs;
		else
			rt->selected_obj = rt->selected_obj->next;
		return (1);
	}
	if (rt_move_light(rt, key))
		return (1);
	if (rt_move_object(rt, key))
		return (1);
	if (rt_rotate_object(rt, key))
		return (1);
	if (rt_resize_object(rt, key))
		return (1);
	return (0);
}
