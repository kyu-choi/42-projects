/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file render_bonus.c
 * @brief Full-frame ray trace and MLX present (bonus).
 *
 * Rendering pipeline:
 *   1. rt_setup_camera — recompute basis from current cam state.
 *   2. Per-row: cast a ray per pixel via rt_ray_from_pixel, trace it,
 *      convert the returned colour to int, write to image buffer.
 *   3. mlx_put_image_to_window — blit the finished image.
 *   4. UI overlay strings drawn AFTER the image blit so they are
 *      visible on top.
 */

/**
 * @brief Trace one row; put pixels to image.
 */
static void	rt_render_row(t_rt *rt, int y)
{
	int		x;
	t_ray	ray;
	t_color	color;

	x = 0;
	while (x < rt->win_w)
	{
		ray = rt_ray_from_pixel(rt, x, y);
		color = rt_trace_ray(&rt->scene, ray);
		rt_put_pixel(&rt->img, x, y, rt_color_to_int(color));
		x++;
	}
}

/**
 * @brief Prints one guide line on the window.
 */
static void	rt_ui_line(t_rt *rt, int y, int color, char *text)
{
	mlx_string_put(rt->mlx, rt->win, 16, y, color, text);
}

/**
 * @brief Draws camera/light control help lines.
 */
static void	rt_draw_ui_cam_light(t_rt *rt)
{
	rt_ui_line(rt, 16, 0xFFD700, "miniRT bonus controls");
	rt_ui_line(rt, 34, 0xFFFFFF, "Cam move: W/S(fwd) A/D(side) Q/E(up)");
	rt_ui_line(rt, 52, 0xFFFFFF, "Cam rotate: Arrow keys");
	rt_ui_line(rt, 70, 0xFFFFFF, "Light: J/L(X) U/O(Y) I/K(Z)  P=cycle");
}

/**
 * @brief Draws selected object transform help lines.
 */
static void	rt_draw_ui_object(t_rt *rt)
{
	rt_ui_line(rt, 96, 0xFFFFFF, "Select object: TAB");
	rt_ui_line(rt, 114, 0xFFFFFF, "Move obj: F/B(X) R/Y(Y) T/G(Z)");
	rt_ui_line(rt, 132, 0xFFFFFF, "Rotate axis: Z/X(yaw) C/V(pitch)");
	rt_ui_line(rt, 150, 0xFFFFFF, "Radius: +/-  Height(cy/co/hy/pa): N/M");
	rt_ui_line(rt, 168, 0xFFFFFF, "Objects: sp pl cy co hy pa");
	rt_ui_line(rt, 186, 0xFFFFFF, "Axes: 1 | Guide: H | Exit: ESC");
}

/**
 * @brief Trace all pixels, present image, then draw help UI overlay.
 */
void	rt_render(t_rt *rt)
{
	int	y;

	y = 0;
	while (y < rt->win_h)
	{
		rt_render_row(rt, y);
		y++;
	}
	if (rt->show_axes)
		rt_draw_debug_axes(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.ptr, 0, 0);
	if (rt->show_axes)
		rt_draw_axis_labels(rt);
	if (rt->show_ui)
	{
		rt_draw_ui_cam_light(rt);
		rt_draw_ui_object(rt);
	}
}
