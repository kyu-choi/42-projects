/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:34:59 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_bonus.h"

/**
 * @file main_bonus.c
 * @brief Program entry point and render-loop bootstrap (bonus).
 *
 * Execution flow:
 *   1. Validate argc == 2 (program + scene.rt).
 *   2. rt_init: parse scene, initialise MLX window + image.
 *   3. Enable window resize (macOS ObjC / Linux no-op).
 *   4. First render (fills image buffer before hooks fire).
 *   5. Register key / expose / destroy / loop hooks.
 *   6. Enter mlx_loop (never returns normally).
 */

/**
 * @brief Entry point: validates args, inits, renders, enters event loop.
 *
 * @param argc Argument count; must be 2.
 * @param argv argv[1] = path to .rt scene file.
 * @return 0 on success; 1 on error.
 */
int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
	{
		rt_error("Usage: ./miniRT scene.rt");
		return (1);
	}
	if (!rt_init(&rt, argv[1]))
		return (1);
	rt_enable_window_resize(&rt);
	rt_render(&rt);
	mlx_key_hook(rt.win, rt_key_press, &rt);
	mlx_expose_hook(rt.win, rt_expose, &rt);
	mlx_hook(rt.win, EVENT_DESTROY, 0, rt_close, &rt);
	mlx_loop_hook(rt.mlx, rt_poll_resize, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
