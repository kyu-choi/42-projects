/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 15:20:56 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file init_bonus.c
 * @brief Scene/MLX initialisation and path validation (bonus).
 *
 * Initialisation sequence:
 *   1. rt_has_rt_extension — reject non-.rt paths.
 *   2. rt_parse_scene     — read + parse the .rt file.
 *   3. rt_setup_camera    — build camera basis from parsed data.
 *   4. rt_init_mlx        — create MLX connection, window, image.
 */

/**
 * @brief Check path ends with ".rt".
 * @param path File path string.
 * @return 1 if valid; 0 otherwise.
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
 * @brief Init MLX, window, image; fetch image data addr.
 * @param rt Runtime context (mlx, win, img filled).
 * @return 1 on success; 0 on error (calls rt_error).
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
 * @brief Full init: parse scene, init MLX; on fail, cleanup.
 * @param rt Runtime; scene, mlx, win, img set on success.
 * @param path Path to .rt file.
 * @return 1 on success; 0 on error.
 */
int	rt_init(t_rt *rt, char *path)
{
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img.ptr = NULL;
	rt->img.addr = NULL;
	rt->selected_obj = NULL;
	rt->selected_light = NULL;
	rt->win_w = WIN_W;
	rt->win_h = WIN_H;
	rt->show_ui = 1;
	rt->show_axes = 0;
	if (!rt_has_rt_extension(path))
		return (rt_error("First argument must be .rt file"));
	if (!rt_parse_scene(path, &rt->scene))
		return (0);
	rt->selected_obj = rt->scene.objs;
	rt->selected_light = rt->scene.lights;
	if (!rt_init_mlx(rt))
	{
		rt_free_scene(&rt->scene);
		rt_destroy_mlx(rt);
		return (0);
	}
	return (1);
}
