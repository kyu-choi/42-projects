/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file hooks_bonus.c
 * @brief MLX event callbacks: key press, expose, resize (bonus).
 *
 * Key press handles ESC (close), H (UI guide toggle), plus camera and
 * scene controls.  The bonus version adds KEY_H for the on-screen
 * help overlay.
 */

/**
 * @brief Rebuilds the image buffer to match a new window size.
 *
 * Creates a new MLX image, destroys the old one, and updates all
 * dimension fields.  WHY a new image: minilibx has no resize API.
 *
 * @param rt Application context.
 * @param w  New width in pixels.
 * @param h  New height in pixels.
 * @return 1 on success; 0 on MLX allocation failure.
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
 * @brief Window resize callback: updates image when size changes.
 *
 * @param w  New width.
 * @param h  New height.
 * @param rt Application context.
 * @return Always 0.
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
 * @brief Key-press handler: ESC → close, H → toggle UI, else controls.
 *
 * @param key  X11/macOS keycode.
 * @param rt   Application context.
 * @return Always 0.
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
 * @brief Expose handler: redraws the frame on window reveal.
 *
 * @param rt Application context.
 * @return Always 0.
 */
int	rt_expose(t_rt *rt)
{
	rt_render(rt);
	return (0);
}
