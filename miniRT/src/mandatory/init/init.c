/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file init.c
 * @brief Scene and MLX initialization for mandatory target.
 *
 * Initialization sequence:
 * 1. Validate .rt file extension (fail fast on wrong input)
 * 2. Parse scene: read file, tokenize lines, build scene struct
 * 3. Create MLX connection, window, and off-screen image buffer
 * 4. Fetch pixel data address for direct memory writes
 *
 * On any failure the function cleans up partially-created resources
 * so the caller can simply return without additional free calls.
 *
 * @note WIN_W/WIN_H (1280x720) are compile-time constants defined in
 *       the header; the window is not resizable on Linux.
 */

/**
 * @brief Checks if path ends with ".rt".
 *
 * Why we check manually instead of using ft_strrchr('.'):
 * - The extension must be exactly ".rt" at the END of the string.
 * - A dot in the middle of the path (e.g., "./my.dir/scene") is not
 *   a valid extension; checking the last 3 characters is simpler and
 *   avoids false positives.
 *
 * @param path File path string.
 * @return 1 if valid .rt extension; 0 otherwise.
 */
static int	rt_has_rt_extension(char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 3)
		return (0);
	if (path[len - 3] != '.')
		return (0);
	if (path[len - 2] != 'r' || path[len - 1] != 't')
		return (0);
	return (1);
}

/**
 * @brief Initializes MLX connection, window, and image buffer.
 *
 * Creates three MLX resources in order:
 * 1. mlx_init()      -> X11/AppKit display connection
 * 2. mlx_new_window  -> visible window at WIN_W x WIN_H
 * 3. mlx_new_image   -> off-screen pixel buffer for ray tracing
 *
 * mlx_get_data_addr returns a pointer to the raw pixel array so we
 * can write pixels directly (faster than mlx_pixel_put per pixel).
 *
 * @param rt Runtime context; mlx, win, img fields are filled.
 * @return 1 on success; 0 on error (calls rt_error with message).
 */
int	rt_init_mlx(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (rt_error("mlx_init failed"));
	rt->win = mlx_new_window(rt->mlx, rt->win_w, rt->win_h, "miniRT");
	if (!rt->win)
		return (rt_error("mlx_new_window failed"));
	rt->img.ptr = mlx_new_image(rt->mlx, rt->win_w, rt->win_h);
	if (!rt->img.ptr)
		return (rt_error("mlx_new_image failed"));
	rt->img.addr = mlx_get_data_addr(rt->img.ptr, &rt->img.bpp,
			&rt->img.line_len, &rt->img.endian);
	if (!rt->img.addr)
		return (rt_error("mlx_get_data_addr failed"));
	rt->img.width = rt->win_w;
	rt->img.height = rt->win_h;
	return (1);
}

/**
 * @brief Full initialization: parse scene, create MLX resources.
 *
 * Sets all pointer fields to NULL first so that cleanup functions
 * (rt_destroy_mlx, rt_free_scene) are safe to call even if init
 * fails partway through.
 *
 * @param rt  Runtime context to initialize.
 * @param path Path to the .rt scene file.
 * @return 1 on success; 0 on error (scene freed, MLX destroyed).
 */
int	rt_init(t_rt *rt, char *path)
{
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img.ptr = NULL;
	rt->img.addr = NULL;
	rt->selected_obj = NULL;
	rt->win_w = WIN_W;
	rt->win_h = WIN_H;
	rt->show_ui = 1;
	rt->show_axes = 0;
	if (!rt_has_rt_extension(path))
		return (rt_error("First argument must be .rt file"));
	if (!rt_parse_scene(path, &rt->scene))
		return (0);
	rt->selected_obj = rt->scene.objs;
	if (!rt_init_mlx(rt))
	{
		rt_free_scene(&rt->scene);
		rt_destroy_mlx(rt);
		return (0);
	}
	return (1);
}
