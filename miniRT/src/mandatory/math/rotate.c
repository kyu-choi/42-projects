/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file rotate.c
 * @brief Rotation around an arbitrary axis using Rodrigues' formula.
 *
 * Rodrigues' rotation formula:
 *   v_rot = v*cos(a) + (k x v)*sin(a) + k*(k . v)*(1 - cos(a))
 *
 * Where k is the unit rotation axis and a is the angle in radians.
 *
 * This is used for:
 * - Camera yaw/pitch rotation (control_camera.c)
 * - Object axis rotation (control_scene.c)
 *
 * @note The axis is normalized internally, so the caller does not
 *       need to pre-normalize it.
 */

/**
 * @brief Rotates vector v around axis by angle radians.
 *
 * @param v     Vector to rotate.
 * @param axis  Rotation axis (normalized internally).
 * @param angle Rotation angle in radians (positive = CCW).
 * @return Rotated vector (same magnitude as v).
 */
t_vec3	rt_rotate_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	a;
	t_vec3	out;
	double	t[3];

	a = rt_norm(axis);
	t[0] = cos(angle);
	t[1] = sin(angle);
	t[2] = rt_dot(a, v);
	out = rt_add(rt_scale(v, t[0]), rt_scale(rt_cross(a, v), t[1]));
	out = rt_add(out, rt_scale(a, t[2] * (1.0 - t[0])));
	return (out);
}
