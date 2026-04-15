/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file rotate_bonus.c
 * @brief Rodrigues' rotation formula: rotate v about axis by angle.
 *
 * v_rot = v·cos θ + (axis × v)·sin θ + axis·(axis·v)·(1 − cos θ).
 * The axis is normalised internally to prevent scaling artefacts.
 */

/**
 * @brief Rotate v around axis by angle. Axis normalized internally.
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
