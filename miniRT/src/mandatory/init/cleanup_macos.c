/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_macos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file cleanup_macos.c
 * @brief macOS-specific MLX cleanup: destroy image and window.
 *
 * On macOS the MLX connection is managed by the AppKit event loop;
 * we only need to destroy the image and window. There is no
 * mlx_destroy_display or free(mlx) call because the macOS MLX
 * uses a static connection internally.
 */

/**
 * @brief Destroys MLX image and window. Safe if rt/mlx is NULL.
 *
 * All pointer fields are set to NULL after destruction to prevent
 * double-free if the function is called again.
 *
 * @param rt Runtime context.
 */
void	rt_destroy_mlx(t_rt *rt)
{
	if (!rt || !rt->mlx)
		return ;
	if (rt->img.ptr)
		mlx_destroy_image(rt->mlx, rt->img.ptr);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img.ptr = NULL;
	rt->img.addr = NULL;
}
