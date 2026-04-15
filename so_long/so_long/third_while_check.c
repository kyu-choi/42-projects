/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_while_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:16:34 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/26 20:16:35 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	third_while_check(char **map, int pec[3], t_point pe_point[2], int i[2])
{
	if (map[i[0]][i[1]] == 'P')
	{
		pec[0]++;
		pe_point[0].x = i[1];
		pe_point[0].y = i[0];
	}
	else if (map[i[0]][i[1]] == 'E')
	{
		pec[1]++;
		pe_point[1].x = i[1];
		pe_point[1].y = i[0];
	}
	else if (map[i[0]][i[1]] == 'C')
		pec[2]++;
	else if (map[i[0]][i[1]] != '0' && map[i[0]][i[1]] != '1')
	{
		ft_printf("Error\n");
		map_free_exit(map);
	}
	i[1]++;
}
