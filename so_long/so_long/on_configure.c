/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_configure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:47:25 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/27 18:47:26 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_configure(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	redraw(game);
	return (0);
}
