/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file pixel.c
 * @brief Direct pixel write to the off-screen image buffer.
 *
 * Uses the raw pixel data pointer (img->addr) obtained from
 * mlx_get_data_addr. This is much faster than mlx_pixel_put
 * because it avoids one X11/AppKit call per pixel.
 *
 * Pixel offset formula:
 *   addr + y * line_len + x * (bpp / 8)
 *
 * @note Bounds check prevents writing outside the image buffer.
 */

/**
 * @brief Writes a single pixel to the image buffer.
 *
 * @param img   Image descriptor (addr, bpp, line_len, width, height).
 * @param x     Pixel column (0-based, left to right).
 * @param y     Pixel row (0-based, top to bottom).
 * @param color 0xRRGGBB packed integer.
 *
 * @note Out-of-bounds coordinates are silently ignored.
 */

void	rt_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}
