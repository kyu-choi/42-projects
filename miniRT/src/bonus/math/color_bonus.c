/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file color_bonus.c
 * @brief Colour operations: construct, add, multiply, modulate, pack.
 *
 * Colours are stored as t_vec3 with channels in [0, 1].  The .rt file
 * uses [0, 255]; conversion happens at parse time (/255).  Packing to
 * 0xRRGGBB happens at render time via rt_color_to_int.
 */

/**
 * @brief Build color from 0-1 components.
 */
t_color	rt_color(double r, double g, double b)
{
	t_color	c;

	c.x = r;
	c.y = g;
	c.z = b;
	return (c);
}

/**
 * @brief Component-wise color addition.
 */
t_color	rt_color_add(t_color a, t_color b)
{
	return (rt_add(a, b));
}

/**
 * @brief Scale color by scalar.
 */
t_color	rt_color_mul(t_color c, double s)
{
	return (rt_scale(c, s));
}

/**
 * @brief Component-wise multiply (modulation).
 */
t_color	rt_color_mod(t_color a, t_color b)
{
	t_color	c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return (c);
}

/**
 * @brief Convert 0-1 color to 0xRRGGBB integer.
 */
int	rt_color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(rt_clamp(c.x, 0.0, 1.0) * 255.0);
	g = (int)(rt_clamp(c.y, 0.0, 1.0) * 255.0);
	b = (int)(rt_clamp(c.z, 0.0, 1.0) * 255.0);
	return ((r << 16) | (g << 8) | b);
}
