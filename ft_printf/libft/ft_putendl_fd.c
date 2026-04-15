/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:16:38 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/27 19:16:59 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	strnum(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	size;

	if (!s)
		return ;
	size = strnum(s);
	write(fd, s, size);
	write(fd, "\n", 1);
}
