/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file vec3_a.c
 * @brief Core 3-D vector operations: construct, add, subtract,
 *        scalar multiply, dot product.
 *
 * t_vec3 is a simple {x, y, z} struct used for both positions and
 * directions. All functions return a new vector (value semantics)
 * to avoid aliasing bugs and keep the call sites concise.
 */

/**
 * @brief Constructs a vec3 from three components.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 * @return New t_vec3{x, y, z}.
 */
t_vec3	rt_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	rt_add(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vec3	rt_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}

/**
 * @brief Scalar multiplication: v * s.
 * @param v Input vector.
 * @param s Scalar factor.
 * @return Scaled vector.
 */
t_vec3	rt_scale(t_vec3 v, double s)
{
	t_vec3	out;

	out.x = v.x * s;
	out.y = v.y * s;
	out.z = v.z * s;
	return (out);
}

/**
 * @brief Dot product: a.x*b.x + a.y*b.y + a.z*b.z.
 *
 * Used throughout the ray tracer for:
 * - Angle between vectors (cos theta = dot(a,b) / (|a|*|b|))
 * - Projection length (dot(v, unit_axis))
 * - Quadratic intersection coefficients
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Scalar dot product.
 */
double	rt_dot(t_vec3 a, t_vec3 b)
{
	double	value;

	value = a.x * b.x;
	value = value + (a.y * b.y);
	value = value + (a.z * b.z);
	return (value);
}
