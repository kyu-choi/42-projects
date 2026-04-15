/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:36:42 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/13 12:36:43 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	first_check(char **map, int size_count[2], int wh[3], int *line_size)
{
	int	i;

	i = 0;
	while (i < size_count[0])
	{
		size_count[1] = ft_strlen(map[i]);
		line_size[i] = size_count[1];
		i++;
	}
	i = 1;
	while (i < size_count[0])
	{
		if (line_size[0] != line_size[i])
		{
			ft_printf("Error\n");
			free(line_size);
			map_free_exit(map);
		}
		i++;
	}
	size_count[1] = line_size[0];
	free(line_size);
	wh[0] = size_count[1];
}

void	second_check(char **map, int size_count[2], int pec[3])
{
	int	i;

	i = 0;
	while (i < size_count[1])
	{
		if (map[0][i] != '1')
		{
			ft_printf("Error\n");
			map_free_exit(map);
		}
		if (map[size_count[0] - 1][i] != '1')
		{
			ft_printf("Error\n");
			map_free_exit(map);
		}
		i++;
	}
	pec[0] = 0;
	pec[1] = 0;
	pec[2] = 0;
}

void	third_check(char **map, int size_count[2], \
int pec[3], t_point pe_point[2])
{
	int	i[2];

	i[0] = 1;
	while (i[0] < size_count[0] - 1)
	{
		i[1] = 1;
		if (map[i[0]][0] != '1')
		{
			ft_printf("Error\n");
			map_free_exit(map);
		}
		if (map[i[0]][size_count[1] - 1] != '1')
		{
			ft_printf("Error\n");
			map_free_exit(map);
		}
		while (i[1] < size_count[1] - 1)
			third_while_check(map, pec, pe_point, i);
		i[0]++;
	}
}

void	four_check(char **map, int pec[3])
{
	if (pec[0] != 1)
	{
		ft_printf("Error\n");
		map_free_exit(map);
	}
	if (pec[1] != 1)
	{
		ft_printf("Error\n");
		map_free_exit(map);
	}
	if (pec[2] == 0)
	{
		ft_printf("Error\n");
		map_free_exit(map);
	}
}

void	map_check(char **map, t_point pe_point[2], int wh[3])
{
	int	size_count[2];
	int	pec[3];
	int	*line_size;

	size_count[0] = 0;
	while (map[size_count[0]])
		size_count[0]++;
	wh[1] = size_count[0];
	line_size = (int *)malloc(sizeof(int) * size_count[0]);
	first_check(map, size_count, wh, line_size);
	second_check(map, size_count, pec);
	third_check(map, size_count, pec, pe_point);
	four_check(map, pec);
	wh[2] = pec[2];
}
