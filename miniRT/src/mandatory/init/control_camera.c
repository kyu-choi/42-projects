/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:34:59 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file control_camera.c
 * @brief Camera translation and rotation via keyboard input.
 *
 * Camera movement is expressed in the camera's own coordinate frame:
 * - Forward/backward: along cam.dir (W/S)
 * - Sideways: along cam.right (A/D)
 * - Vertical: along cam.up (Q/E)
 *
 * Rotation uses rt_rotate_axis (Rodrigues formula):
 * - Yaw (left/right): rotate cam.dir around world-Y axis
 * - Pitch (up/down): rotate cam.dir around cam.right axis
 *
 * After any rotation the camera basis (right, up) is recomputed
 * via rt_setup_camera to keep the coordinate frame orthonormal.
 *
 * @note STEP_MOVE = 0.8 world units; STEP_ROT ~ 5 degrees.
 */

/**
 * @brief Move camera along its forward direction (W/S).
 * @param rt  Runtime context.
 * @param key KEY_W (forward) or KEY_S (backward).
 * @return 1 if key matched; 0 otherwise.
 */
static int	rt_move_fb(t_rt *rt, int key)
{
	if (key == KEY_W)
		rt->scene.cam.pos = rt_add(rt->scene.cam.pos,
				rt_scale(rt->scene.cam.dir, STEP_MOVE));
	else if (key == KEY_S)
		rt->scene.cam.pos = rt_add(rt->scene.cam.pos,
				rt_scale(rt->scene.cam.dir, -STEP_MOVE));
	else
		return (0);
	return (1);
}

/**
 * @brief Move camera sideways (A/D) or vertically (Q/E).
 * @param rt  Runtime context.
 * @param key KEY_A/D (left/right) or KEY_Q/E (up/down).
 * @return 1 if key matched; 0 otherwise.
 */
static int	rt_move_side(t_rt *rt, int key)
{
	if (key == KEY_A)
		rt->scene.cam.pos = rt_add(rt->scene.cam.pos,
				rt_scale(rt->scene.cam.right, -STEP_MOVE));
	else if (key == KEY_D)
		rt->scene.cam.pos = rt_add(rt->scene.cam.pos,
				rt_scale(rt->scene.cam.right, STEP_MOVE));
	else if (key == KEY_Q)
		rt->scene.cam.pos = rt_add(rt->scene.cam.pos,
				rt_scale(rt->scene.cam.up, STEP_MOVE));
	else if (key == KEY_E)
		rt->scene.cam.pos = rt_add(rt->scene.cam.pos,
				rt_scale(rt->scene.cam.up, -STEP_MOVE));
	else
		return (0);
	return (1);
}

/**
 * @brief Rotate camera direction around Y-axis or right-axis.
 *
 * LEFT/RIGHT: yaw around world-up (0,1,0)
 * UP/DOWN:    pitch around cam.right
 *
 * After rotation the direction is re-normalized and the camera
 * basis vectors are recomputed (rt_setup_camera).
 *
 * @param rt  Runtime context.
 * @param key Arrow key code.
 * @return 1 if key matched; 0 otherwise.
 */
static int	rt_rotate_cam(t_rt *rt, int key)
{
	t_vec3	axis;
	double	angle;

	if (key != KEY_LEFT && key != KEY_RIGHT
		&& key != KEY_UP && key != KEY_DOWN)
		return (0);
	axis = rt_vec3(0.0, 1.0, 0.0);
	angle = STEP_ROT;
	if (key == KEY_RIGHT)
		angle = -STEP_ROT;
	if (key == KEY_UP || key == KEY_DOWN)
	{
		axis = rt->scene.cam.right;
		if (key == KEY_DOWN)
			angle = -STEP_ROT;
	}
	rt->scene.cam.dir = rt_rotate_axis(rt->scene.cam.dir, axis, angle);
	rt->scene.cam.dir = rt_norm(rt->scene.cam.dir);
	return (rt_setup_camera(&rt->scene.cam));
}

/**
 * @brief Dispatches camera control: translation then rotation.
 * @param rt  Runtime context.
 * @param key Key code to test.
 * @return 1 if any camera key was handled; 0 otherwise.
 */
int	rt_control_camera(t_rt *rt, int key)
{
	if (rt_move_fb(rt, key))
		return (1);
	if (rt_move_side(rt, key))
		return (1);
	if (rt_rotate_cam(rt, key))
		return (1);
	return (0);
}
