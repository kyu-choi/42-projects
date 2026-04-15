/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file hooks.c
 * @brief MLX event callbacks: key press, expose, window resize.
 *
 * This module wires user input and window events to the rendering
 * pipeline. Each callback follows MLX convention: return 0 and
 * accept the rt context via the void* param registered at hook time.
 *
 * Key design decisions:
 * - rt_rebuild_image creates a NEW image buffer when the window size
 *   changes, then destroys the old one (avoids writing past bounds).
 * - rt_key_press batches camera + scene changes and re-renders once.
 * - rt_expose simply re-renders (handles window un-minimize, overlap).
 */

/**
 * @brief Rebuilds the off-screen image buffer to match a new size.
 *
 * Why we create a new image instead of reusing the old one:
 * - MLX images are fixed-size at creation; there is no resize API.
 * - We must create a new image, copy the data-address pointer, then
 *   destroy the old image to avoid a memory leak.
 *
 * @param rt Runtime context (img, win_w, win_h updated on success).
 * @param w  New width in pixels.
 * @param h  New height in pixels.
 * @return 1 on success; 0 on mlx_new_image / get_data_addr failure.
 */
static int	rt_rebuild_image(t_rt *rt, int w, int h)
{
	void	*new_ptr;
	char	*new_addr;

	new_ptr = mlx_new_image(rt->mlx, w, h);
	if (!new_ptr)
		return (0);
	new_addr = mlx_get_data_addr(new_ptr, &rt->img.bpp,
			&rt->img.line_len, &rt->img.endian);
	if (!new_addr)
		return (mlx_destroy_image(rt->mlx, new_ptr), 0);
	if (rt->img.ptr)
		mlx_destroy_image(rt->mlx, rt->img.ptr);
	rt->img.ptr = new_ptr;
	rt->img.addr = new_addr;
	rt->img.width = w;
	rt->img.height = h;
	rt->win_w = w;
	rt->win_h = h;
	return (1);
}

/**
 * @brief ConfigureNotify callback; re-renders when window size changes.
 *
 * Called on macOS via rt_poll_resize (loop-hook). On Linux this is a
 * no-op because minilibx-linux locks the window size and calling
 * mlx_hook(EVENT_CONFIGURE) causes a segfault due to a calling-
 * convention mismatch in the MLX event dispatch.
 *
 * @param w  New window width.
 * @param h  New window height.
 * @param rt Runtime context.
 * @return 0 (MLX convention).
 *
 * @note Ignores sizes < 1 and unchanged sizes to avoid useless work.
 */
int	rt_on_resize(int w, int h, t_rt *rt)
{
	if (w < 1 || h < 1)
		return (0);
	if (w == rt->win_w && h == rt->win_h)
		return (0);
	if (rt_rebuild_image(rt, w, h))
		rt_render(rt);
	return (0);
}

/**
 * @brief Key-press callback dispatched by mlx_key_hook.
 *
 * Priority order:
 * 1. ESC -> close window and exit immediately
 * 2. H   -> toggle UI overlay (no re-trace, just re-render)
 * 3. Camera movement / rotation keys
 * 4. Scene controls (TAB select, object move/rotate/resize, light)
 *
 * Only re-renders if a camera or scene key was actually handled,
 * avoiding unnecessary full-frame traces on unbound keys.
 *
 * @param key  Key code (platform-specific, see KEY_* macros).
 * @param rt   Runtime context.
 * @return 0 (MLX convention).
 */
int	rt_key_press(int key, t_rt *rt)
{
	int	changed;

	if (key == KEY_ESC)
		rt_close(rt);
	if (key == KEY_H)
		return (rt->show_ui = !rt->show_ui, rt_render(rt), 0);
	if (key == KEY_1)
		return (rt->show_axes = !rt->show_axes, rt_render(rt), 0);
	changed = 0;
	if (rt_control_camera(rt, key))
		changed = 1;
	if (rt_control_scene(rt, key))
		changed = 1;
	if (changed)
		rt_render(rt);
	return (0);
}

/**
 * @brief Expose handler: redraws the image on window refresh.
 * @param rt rt context
 * @return 0 (MLX convention)
 */
int	rt_expose(t_rt *rt)
{
	rt_render(rt);
	return (0);
}
