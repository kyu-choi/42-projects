/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_camera_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file control_camera_bonus.c
 * @brief Camera movement and rotation controls (bonus).
 *
 * The camera uses a local coordinate frame:
 *   forward = cam.dir,  sideways = cam.right,  vertical = world Y.
 * Movement keys: W/S (forward/back), A/D (left/right), Q/E (up/down).
 * Rotation keys: arrows → yaw (left/right) and pitch (up/down).
 */

/**
 * @brief Move camera forward/back along dir.
 * @return 1 if W/S; 0 otherwise.
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
 * @brief Strafe camera along right/up.
 * @return 1 if A/D/Q/E; 0 otherwise.
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
 * @brief Rotate camera dir; arrows. Recomputes right/up.
 * @return 1 if arrow key; 0 otherwise.
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
 * @brief Dispatch camera control by key.
 * @return 1 if handled; 0 otherwise.
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
