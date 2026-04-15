/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_linux_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:35:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file cleanup_linux_bonus.c
 * @brief Linux-specific MLX resource teardown (bonus).
 *
 * Destroys image → window → display in that order, then frees the
 * mlx pointer.  The display handle must be destroyed last because
 * image and window depend on it.
 */

int	mlx_destroy_display(void *mlx_ptr);

/**
 * @brief Free image, window, display; free mlx ptr (Linux).
 */
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
