/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:10:17 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/15 14:10:18 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid(int y, int x, int **visited, int wh[3])
{
	if (!((0 <= y && y < wh[1]) && (0 <= x && x < wh[0])))
		return (0);
	if (visited[y][x] == 1)
		return (0);
	return (1);
}

void	first_valid(t_inform *inform, int wh[3])
{
	int	i;
	int	j;

	inform->c_count_exit_exist[0] = 0;
	inform->c_count_exit_exist[1] = 0;
	inform->visited = (int **)malloc(sizeof(int *) * wh[1]);
	i = 0;
	while (i < wh[1])
	{
		(inform->visited)[i] = (int *)malloc(sizeof(int) * wh[0]);
		i++;
	}
	i = 0;
	while (i < wh[1])
	{
		j = 0;
		while (j < wh[0])
		{
			(inform->visited)[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	valid_if(t_inform *inform, int x, int y, char **map)
{
	enqueue(&(inform->valid_queue), x, y);
	(inform->visited)[y][x] = 1;
	if (map[y][x] == 'C')
		(inform->c_count_exit_exist)[0]++;
	else if (map[y][x] == 'E')
		(inform->c_count_exit_exist)[1] = 1;
}

void	second_valid(char **map, t_inform *inform, int wh[3])
{
	while (!is_empty(&(inform->valid_queue)))
	{
		(inform->pointed) = dequeue(&(inform->valid_queue));
		if (valid((inform->pointed).y, (inform->pointed).x + 1, \
		inform->visited, wh) && map[(inform->pointed).y] \
		[(inform->pointed).x + 1] != '1')
			valid_if(inform, (inform->pointed).x + 1, (inform->pointed).y, map);
		if (valid((inform->pointed).y + 1, (inform->pointed).x, \
		inform->visited, wh) && map[(inform->pointed).y + 1] \
		[(inform->pointed).x] != '1')
			valid_if(inform, (inform->pointed).x, (inform->pointed).y + 1, map);
		if (valid((inform->pointed).y, (inform->pointed).x - 1, \
		inform->visited, wh) && map[(inform->pointed).y] \
		[(inform->pointed).x - 1] != '1')
			valid_if(inform, (inform->pointed).x - 1, (inform->pointed).y, map);
		if (valid((inform->pointed).y - 1, (inform->pointed).x, \
		inform->visited, wh) && map[(inform->pointed).y - 1] \
		[(inform->pointed).x] != '1')
			valid_if(inform, (inform->pointed).x, (inform->pointed).y - 1, map);
		if ((inform->c_count_exit_exist)[0] == wh[2] && \
		(inform->c_count_exit_exist)[1] == 1)
			break ;
	}
}

int	map_valid(char **map, t_point pe_point[2], int wh[3])
{
	t_inform	inform;
	int			i[2];

	first_valid(&inform, wh);
	init_queue(&(inform.valid_queue), wh[0], wh[1]);
	enqueue(&(inform.valid_queue), pe_point[0].x, pe_point[0].y);
	(inform.visited)[pe_point[0].y][pe_point[0].x] = 1;
	second_valid(map, &inform, wh);
	i[0] = 0;
	while (i[0] < wh[1])
	{
		free((inform.visited)[i[0]]);
		i[0]++;
	}
	free(inform.visited);
	free((inform.valid_queue).data);
	if ((inform.c_count_exit_exist)[0] == wh[2] && \
	(inform.c_count_exit_exist)[1] == 1)
		return (1);
	else
		return (0);
}
