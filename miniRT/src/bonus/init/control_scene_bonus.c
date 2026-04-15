/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_scene_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file control_scene_bonus.c
 * @brief Scene-object controls (bonus): TAB select, move/rotate/resize.
 *
 * Key mapping (bonus extends mandatory with cone/hyperboloid/paraboloid):
 *   P           — cycle active light (multi-light).
 *   J/L I/K U/O — move active light (X / Z / Y).
 *   F/B T/G R/Y — move selected object.
 *   Z/X C/V     — rotate selected object axis.
 *   +/−         — resize radius (sphere/cylinder/cone/hy/pa).
 *   N/M         — resize height (cylinder/cone/hy/pa only).
 *   TAB         — cycle object selection.
 */

/**
 * @brief Moves the currently selected light along world axes.
 *
 * In bonus mode, if a selected_light exists, that light is moved;
 * otherwise the head of the light list (or primary light) is moved.
 *
 * @param rt  Application context.
 * @param key Keycode.
 * @return 1 if light was moved; 0 otherwise.
 */
static int	rt_move_light(t_rt *rt, int key)
{
	t_vec3	*pos;

	if (rt->selected_light)
		pos = &rt->selected_light->light.pos;
	else if (rt->scene.lights)
		pos = &rt->scene.lights->light.pos;
	else
		pos = &rt->scene.light.pos;
	if (key == KEY_J)
		pos->x -= STEP_MOVE;
	else if (key == KEY_L)
		pos->x += STEP_MOVE;
	else if (key == KEY_U)
		pos->y += STEP_MOVE;
	else if (key == KEY_O)
		pos->y -= STEP_MOVE;
	else if (key == KEY_I)
		pos->z += STEP_MOVE;
	else if (key == KEY_K)
		pos->z -= STEP_MOVE;
	else
		return (0);
	return (1);
}

/**
 * @brief Moves the selected object's position.
 *
 * For planes, obj->point is translated; for all others, obj->center.
 *
 * @param rt  Application context.
 * @param key Keycode (F/B/T/G/R/Y).
 * @return 1 if moved; 0 if no selection or unrelated key.
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
 * @brief Rotates the selected object's axis direction.
 *
 * Spheres have no meaningful axis and are skipped.
 *
 * @param rt  Application context.
 * @param key Keycode (Z/X = Y-axis, C/V = X-axis).
 * @return 1 if rotated; 0 otherwise.
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
 * @brief Resizes the selected object (radius via +/−, height via N/M).
 *
 * Planes have no size parameter and are skipped.  Minimum radius is
 * clamped to STEP_SIZE to prevent zero-size objects.
 *
 * @param rt  Application context.
 * @param key Keycode.
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
	if (obj->type == OBJ_CYLINDER || obj->type == OBJ_CONE
		|| obj->type == OBJ_HYPERBOLOID || obj->type == OBJ_PARABOLOID)
	{
		if (key == KEY_N)
			return (obj->height += STEP_SIZE, 1);
		if (key == KEY_M)
			return (obj->height = rt_clamp(obj->height - STEP_SIZE,
					STEP_SIZE, 1e9), 1);
	}
	return (0);
}

/**
 * @brief Dispatch scene control: TAB, P, light, move, rotate, resize.
 * @return 1 if handled; 0 otherwise.
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
	if (key == KEY_P && rt->scene.lights)
	{
		if (!rt->selected_light || !rt->selected_light->next)
			rt->selected_light = rt->scene.lights;
		else
			rt->selected_light = rt->selected_light->next;
		return (1);
	}
	if (rt_move_light(rt, key))
		return (1);
	if (rt_move_object(rt, key))
		return (1);
	if (rt_rotate_object(rt, key))
		return (1);
	return (rt_resize_object(rt, key));
}
