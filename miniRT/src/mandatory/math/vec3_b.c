/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file vec3_b.c
 * @brief Extended vector operations: length, normalize, cross product,
 *        negate, and scalar clamp.
 *
 * These are used heavily in intersection tests and shading:
 * - rt_norm: unit-length directions for rays and normals
 * - rt_cross: camera basis (right = dir x up), surface tangent
 * - rt_clamp: constraining color components to [0, 1]
 */

/**
 * @brief Euclidean length: sqrt(v . v).
 * @param v Input vector.
 * @return |v|; 0.0 if the vector is zero or negative dot.
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
 * @brief Normalize: v / |v|. Returns zero vector if |v| < EPS.
 *
 * EPS guard prevents division by zero for degenerate vectors
 * (e.g., a camera direction of (0,0,0) after bad parsing).
 *
 * @param v Input vector.
 * @return Unit-length vector in same direction, or (0,0,0).
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
 * @brief Cross product: a x b.
 *
 * Produces a vector perpendicular to both a and b. Used to build
 * the camera's right/up basis vectors and to compute surface
 * tangent frames for UV mapping.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Perpendicular vector (magnitude = |a|*|b|*sin(theta)).
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
 * @brief Negate: returns -v (flips all components).
 * @param v Input vector.
 * @return Negated vector.
 */
t_vec3	rt_neg(t_vec3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

/**
 * @brief Clamps a scalar to [min, max].
 *
 * Used primarily for clamping color channels to [0.0, 1.0]
 * and preventing object dimensions from going to zero.
 *
 * @param value Input value.
 * @param min   Lower bound.
 * @param max   Upper bound.
 * @return Clamped value.
 */
double	rt_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
