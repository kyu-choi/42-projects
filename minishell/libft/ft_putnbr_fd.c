/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:42:36 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/01/07 18:07:05 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_putnbr_fd - Write an integer to a file descriptor
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	void ft_putnbr_fd(int n, int fd);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_putnbr_fd() function writes the integer 'n' to the given file 
 * 	descriptor. It handles negative numbers properly by outputting the 
 * 	'-' sign.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	None.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	num;

	num = n;
	if (num < 0)
	{
		num = -num;
		ft_putchar_fd('-', fd);
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	ft_putchar_fd((num % 10) + '0', fd);
}
