/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:17:09 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/27 19:17:21 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	nbsign(int nb, int fd)
{
	if (nb == 0)
	{
		write(fd, "0", 1);
		nb = 0;
	}
	else if (nb == -2147483648)
	{
		write(fd, "-2", 2);
		nb = 147483648;
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb = nb * -1;
	}
	return (nb);
}

static	void	ft_putnbr(int nb, int fd)
{
	char	a;

	nb = nbsign(nb, fd);
	if (nb > 9)
	{
		ft_putnbr(nb / 10, fd);
		ft_putnbr(nb % 10, fd);
	}
	else if (nb > 0 && nb < 10)
	{
		a = '0' + nb;
		write(fd, &a, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}
