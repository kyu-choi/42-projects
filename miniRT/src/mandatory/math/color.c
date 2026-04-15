/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file color.c
 * @brief Color arithmetic in floating-point [0, 1] range.
 *
 * Colors are stored as t_color (alias for t_vec3) where:
 * - x = red, y = green, z = blue, all in [0.0, 1.0]
 *
 * This representation simplifies arithmetic (add, multiply, modulate)
 * and defers the integer conversion (0xRRGGBB) to the final step
 * when writing pixels to the image buffer.
 *
 * @note .rt files use 0-255 integer colors; the parser converts to
 *       float immediately (value / 255.0).
 */

/**
 * @brief Constructs a color from [0,1] float components.
 * @param r Red channel.
 * @param g Green channel.
 * @param b Blue channel.
 * @return New t_color.
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
 * @brief Returns a + b (component-wise).
 */
t_color	rt_color_add(t_color a, t_color b)
{
	return (rt_add(a, b));
}

/**
 * @brief Returns c * s.
 */
t_color	rt_color_mul(t_color c, double s)
{
	return (rt_scale(c, s));
}

/**
 * @brief Component-wise modulation: (a.r*b.r, a.g*b.g, a.b*b.b).
 *
 * Used to apply a colored light to a surface color: each channel
 * of the light multiplies the corresponding surface channel.
 *
 * @param a First color (typically surface).
 * @param b Second color (typically light).
 * @return Modulated color.
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
 * @brief Converts [0,1] float color to packed 0xRRGGBB integer.
 *
 * Each channel is clamped to [0,1], scaled to 0-255, then packed:
 *   (r << 16) | (g << 8) | b
 *
 * @param c Float color.
 * @return 24-bit packed integer suitable for rt_put_pixel.
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
