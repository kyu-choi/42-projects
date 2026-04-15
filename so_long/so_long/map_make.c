/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:50:27 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/15 12:50:28 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	make_map(int size, char ***map, int fd, char **argv)
{
	char	*ch;
	int		i;
	int		len;

	*map = (char **)malloc(sizeof(char *) * (size + 1));
	if (*map == NULL)
		return ;
	(*map)[size] = NULL;
	fd = open(argv[1], O_RDONLY);
	ch = get_next_line(fd);
	i = 0;
	while (ch != NULL)
	{
		len = ft_strlen(ch);
		if (len > 0 && ch[len - 1] == '\n')
			ch[len - 1] = '\0';
		(*map)[i] = ft_strdup(ch);
		i++;
		free(ch);
		ch = get_next_line(fd);
	}
	close(fd);
}

void	map_make(int argc, char **argv, char ***map)
{
	int		fd;
	int		size;
	char	*ch;

	if (argc != 2)
	{
		ft_printf("Error\n");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	ch = get_next_line(fd);
	size = 0;
	while (ch != NULL)
	{
		size++;
		free(ch);
		ch = get_next_line(fd);
	}
	close(fd);
	make_map(size, map, fd, argv);
}
