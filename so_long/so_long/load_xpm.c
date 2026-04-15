/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:11:10 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/18 20:11:11 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_xpm(t_game *game, char **map, int wh[3], t_point pe_point[2])
{
	int	img_w;
	int	img_h;

	game->prince = mlx_xpm_file_to_image(game->mlx, "왕자.xpm", &img_w, &img_h);
	game->before_princess = mlx_xpm_file_to_image(game->mlx, \
	"공주_닫힘.xpm", &img_w, &img_h);
	game->after_princess = mlx_xpm_file_to_image(game->mlx, \
	"공주_열림.xpm", &img_w, &img_h);
	game->floor = mlx_xpm_file_to_image(game->mlx, "바닥.xpm", &img_w, &img_h);
	game->wall = mlx_xpm_file_to_image(game->mlx, "벽.xpm", &img_w, &img_h);
	game->monster = mlx_xpm_file_to_image(game->mlx, "괴물.xpm", &img_w, &img_h);
	game->map = map;
	game->w = wh[0];
	game->h = wh[1];
	game->c_count = wh[2];
	game->steps = 0;
	game->px = pe_point[0].x;
	game->py = pe_point[0].y;
	game->curr_princess = game->before_princess;
}
