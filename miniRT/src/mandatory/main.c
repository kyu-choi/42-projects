/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:20:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/16 01:34:59 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @file main.c
 * @brief Program entry point for mandatory miniRT binary.
 *
 * Execution flow:
 * 1. Validate argc == 2 (program name + .rt file path)
 * 2. rt_init: parse scene file, create MLX window and image buffer
 * 3. rt_enable_window_resize: platform-specific resize (no-op on Linux)
 * 4. rt_render: trace every pixel and present initial frame
 * 5. Register MLX hooks (key, expose, destroy, loop)
 * 6. mlx_loop: event loop (never returns under normal operation)
 *
 * @note mlx_loop blocks forever; cleanup happens in rt_close via hook.
 */

/**
 * @brief Entry point: parse scene, init MLX, render, enter event loop.
 *
 * Why hooks are registered AFTER the first render:
 * - If we register expose before rendering, the first expose event
 *   triggers a render before the scene is fully drawn, causing flicker.
 * - Rendering first ensures the user sees a complete frame immediately.
 *
 * @param argc Must be 2 (program + .rt path).
 * @param argv argv[1] is the path to the .rt scene file.
 * @return 1 on argument/init error; 0 on success (never reached).
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
