/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:10 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/07/31 17:14:11 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_queue
{
	t_point	*data;
	int		front;
	int		rear;
	int		capacity;
}	t_queue;

typedef struct s_game
{
	void	*prince;
	void	*before_princess;
	void	*after_princess;
	void	*curr_princess;
	void	*floor;
	void	*wall;
	void	*monster;
	void	*mlx;
	void	*win;
	char	**map;
	int		px;
	int		py;
	int		w;
	int		h;
	int		c_count;
	int		steps;
	int		paused;
}	t_game;

typedef struct s_inform
{
	t_queue	valid_queue;
	int		**visited;
	int		c_count_exit_exist[2];
	t_point	pointed;
}	t_inform;

void	init_queue(t_queue *q, int w, int h);
int		is_empty(t_queue *q);
void	enqueue(t_queue *q, int x, int y);
t_point	dequeue(t_queue *q);

void	map_make(int argc, char **argv, char ***map);
void	map_check(char **map, t_point PE_point[2], int wh[3]);
void	third_while_check(char **map, int PEC[3], \
t_point PE_point[2], int i[2]);
//void	while_check(char **map, int i, int count);
//void	while_check_2(char **map, int i[2], t_point PE_point[2], int PEC[3]);

int		map_valid(char **map, t_point PE_point[2], int wh[3]);
int		valid(int y, int x, int **visited, int wh[3]);

void	load_xpm(t_game *game, char **map, int wh[3], t_point PE_point[2]);

void	lender(t_game *game);

void	clean_game(t_game *game);
int		esc_key(int keycode, void *param);
int		close_click(void *param);
int		on_key(int keycode, void *param);
int		size_handle(void *param);

void	redraw(t_game *game);

int		on_configure(void *param);
int		on_map(void *param);
int		un_map(void *param);

void	map_free_exit(char **map);

#endif
