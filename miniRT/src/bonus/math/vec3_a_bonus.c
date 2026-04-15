/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_a_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file vec3_a_bonus.c
 * @brief Vec3 constructors and basic arithmetic: add, sub, scale, dot.
 *
 * All operations return new values (no mutation) for safe chaining.
 */

/**
 * @brief Build vec3 from components.
 */
t_vec3	rt_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * @brief Component-wise addition.
 */
t_vec3	rt_add(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

/**
 * @brief Component-wise subtraction a - b.
 */
t_vec3	rt_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}

/**
 * @brief Scale vector by scalar.
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
 * @brief Dot product.
 */
double	rt_dot(t_vec3 a, t_vec3 b)
{
	double	value;

	value = a.x * b.x;
	value = value + (a.y * b.y);
	value = value + (a.z * b.z);
	return (value);
}
