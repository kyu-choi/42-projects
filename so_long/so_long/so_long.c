/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:17:22 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/13 12:17:22 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	t_point	pe_point[2];
	int		wh[3];
	t_game	game;

	map_make(argc, argv, &map);
	map_check(map, pe_point, wh);
	if (!map_valid(map, pe_point, wh))
	{
		ft_printf("Error\n");
		map_free_exit(map);
	}
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, wh[0] * 64, wh[1] * 64, "so_long");
	load_xpm(&game, map, wh, pe_point);
	lender(&game);
	mlx_expose_hook(game.win, size_handle, &game);
	mlx_hook(game.win, 22, StructureNotifyMask, on_configure, &game);
	mlx_hook(game.win, 19, StructureNotifyMask, on_map, &game);
	mlx_hook(game.win, 18, StructureNotifyMask, un_map, &game);
	mlx_hook(game.win, 17, StructureNotifyMask, close_click, &game);
	mlx_key_hook(game.win, on_key, &game);
	mlx_loop(game.mlx);
	return (0);
}
