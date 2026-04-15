/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:47:29 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/27 18:47:30 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	redraw(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	lender(game);
}

int	first_on_key(t_game *game, int keycode, int d_xy[2], int n_xy[2])
{
	d_xy[0] = 0;
	d_xy[1] = 0;
	if (keycode == XK_Escape)
		clean_game(game);
	else if (keycode == XK_Left || keycode == XK_a)
		d_xy[0] = -1;
	else if (keycode == XK_Right || keycode == XK_d)
		d_xy[0] = +1;
	else if (keycode == XK_Up || keycode == XK_w)
		d_xy[1] = -1;
	else if (keycode == XK_Down || keycode == XK_s)
		d_xy[1] = +1;
	else if (d_xy[0] == 0 && d_xy[1] == 0)
		return (-1);
	n_xy[0] = game->px + d_xy[0];
	n_xy[1] = game->py + d_xy[1];
	if (n_xy[0] < 0 || n_xy[0] >= game->w || n_xy[1] < 0 || n_xy[1] >= game->h)
		return (-1);
	return (0);
}

void	second_on_key(t_game *game, int n_xy[2], char n)
{
	game->px = n_xy[0];
	game->py = n_xy[1];
	game->steps++;
	ft_printf("%d\n", game->steps);
	if (n == 'C')
	{
		game->c_count--;
		game->map[n_xy[1]][n_xy[0]] = '0';
		if (game->c_count == 0)
			game->curr_princess = game->after_princess;
	}
	if (n == 'E' && game->c_count == 0)
	{
		clean_game(game);
		exit(0);
	}
	redraw(game);
}

int	on_key(int keycode, void *param)
{
	int		d_xy[2];
	int		n_xy[2];
	t_game	*game;
	char	n;
	int		val;

	game = (t_game *)param;
	val = first_on_key(game, keycode, d_xy, n_xy);
	if (val == -1)
		return (0);
	n = game->map[n_xy[1]][n_xy[0]];
	if (n == '1')
		return (0);
	second_on_key(game, n_xy, n);
	return (0);
}
