/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_linux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:34:59 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file cleanup_linux.c
 * @brief Linux-specific MLX cleanup: destroy image, window, display.
 *
 * On Linux, minilibx-linux allocates an X11 Display* internally.
 * Unlike macOS, we must call mlx_destroy_display() and then free()
 * the mlx pointer to avoid leaking the Display handle.
 *
 * Cleanup order matters:
 * 1. Destroy image  (depends on mlx)
 * 2. Destroy window (depends on mlx + display)
 * 3. Destroy display (frees X11 connection)
 * 4. free(mlx)      (frees the t_xvar struct)
 *
 * @note mlx_destroy_display is a minilibx-linux extension not present
 *       in the macOS version, so we forward-declare it here.
 */

/**
 * @brief Destroys all MLX resources and frees the connection.
 *
 * Safe to call even if rt or rt->mlx is NULL (guard checks).
 * After this call all pointers are set to NULL to prevent
 * double-free on subsequent calls.
 *
 * @param rt Runtime context.
 */

int	mlx_destroy_display(void *mlx_ptr);

void	rt_destroy_mlx(t_rt *rt)
{
	if (!rt || !rt->mlx)
		return ;
	if (rt->img.ptr)
		mlx_destroy_image(rt->mlx, rt->img.ptr);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	rt->mlx = NULL;
	rt->win = NULL;
	rt->img.ptr = NULL;
	rt->img.addr = NULL;
}
