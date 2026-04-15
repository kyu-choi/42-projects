/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:34:59 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file resize_linux.c
 * @brief Linux window-resize stubs (no-ops).
 *
 * On Linux, minilibx-linux locks the window to a fixed size via
 * mlx_int_anti_resize_win (sets X11 min/max size hints equal).
 * Overriding this requires X11 API calls (XSetWMNormalHints),
 * which are NOT in the allowed function list per the subject PDF.
 *
 * Additionally, registering mlx_hook(EVENT_CONFIGURE, ...) on Linux
 * causes a segfault because minilibx dispatches ConfigureNotify
 * through mlx_int_param_generic which calls hook(param) with only
 * ONE argument, while rt_on_resize expects THREE.
 *
 * Therefore both functions are safe no-ops on Linux.
 */

/**
 * @brief No-op: Linux MLX locks window size; resize not possible.
 * @param rt Unused.
 */
void	rt_enable_window_resize(t_rt *rt)
{
	(void)rt;
}

/**
 * @brief No-op: Linux has no runtime resize; always returns 0.
 * @param rt Unused.
 * @return 0 (MLX loop-hook convention).
 */
int	rt_poll_resize(t_rt *rt)
{
	(void)rt;
	return (0);
}
