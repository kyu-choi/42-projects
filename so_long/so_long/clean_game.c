/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:46:52 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/27 18:46:53 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_game(t_game *game)
{
	int	i[2];

	if (game->prince)
		mlx_destroy_image(game->mlx, game->prince);
	if (game->before_princess)
		mlx_destroy_image(game->mlx, game->before_princess);
	if (game->after_princess)
		mlx_destroy_image(game->mlx, game->after_princess);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->monster)
		mlx_destroy_image(game->mlx, game->monster);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	i[0] = 0;
	while (i[0] < game->h)
	{
		free(game->map[i[0]]);
		i[0]++;
	}
	free(game->map);
	exit(0);
}
