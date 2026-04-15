/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:06:53 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/19 19:06:54 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	while_lender(int x, int y, t_game *game, char **map)
{
	char	tile;

	y = 0;
	while (y < game->h)
	{
		x = 0;
		while (x < game->w)
		{
			tile = map[y][x];
			mlx_put_image_to_window(game->mlx, game->win, \
			game->floor, x * 64, y * 64);
			if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->wall, x * 64, y * 64);
			else if (tile == 'C')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->monster, x * 64, y * 64);
			else if (tile == 'E')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->curr_princess, x * 64, y * 64);
			x++;
		}
		y++;
	}
}

void	lender(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	map = game->map;
	x = 0;
	y = 0;
	while_lender(x, y, game, map);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->prince, game->px * 64, game->py * 64);
}
