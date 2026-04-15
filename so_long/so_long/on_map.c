/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:47:17 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/27 18:47:17 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_map(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->paused = 0;
	redraw(game);
	return (0);
}
