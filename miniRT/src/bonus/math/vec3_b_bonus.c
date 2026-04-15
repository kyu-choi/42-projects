/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_b_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file vec3_b_bonus.c
 * @brief Vec3 utilities: length, normalise, cross, negate, clamp.
 *
 * rt_norm guards against zero-length vectors (returns (0,0,0) when
 * length < EPS).
 */

/**
 * @brief Euclidean length.
 */
double	rt_len(t_vec3 v)
{
	double	s;

	s = rt_dot(v, v);
	if (s <= 0.0)
		return (0.0);
	return (sqrt(s));
}

/**
 * @brief Unit vector; zero if length < EPS.
 */
t_vec3	rt_norm(t_vec3 v)
{
	double	len;

	len = rt_len(v);
	if (len < EPS)
		return (rt_vec3(0.0, 0.0, 0.0));
	return (rt_scale(v, 1.0 / len));
}

/**
 * @brief Cross product a x b.
 */
t_vec3	rt_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

/**
 * @brief Negate components.
 */
t_vec3	rt_neg(t_vec3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

/**
 * @brief Clamp value to [min, max].
 */
double	rt_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
