/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:31:35 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/01 17:48:49 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man toupper - convert lowercase to uppercase
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <ctype.h>
 *
 *	int	toupper(int c);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	This function convert lowercase letters to uppercase, and vice versa.
 * 
 * 	If c is a lowercase letter, toupper() returns its uppercase 
 * 	equivalent, if an uppercase representation exists in the current 
 * 	locale. Otherwise, it returns c.
 * 
 * 	If c is neither an unsigned char value nor EOF, the behavior of these 
 * 	function is undefined.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The value returned is that of the converted letter, or c if the 
 * 	conversion was not possible.
 * -------------------------------------------------------------------------- *
 */

#include <stdio.h>
#include <limits.h>

int	ft_toupper(int c)
{
	if (c == EOF)
		return (EOF);
	if (c < 0 || c > UCHAR_MAX)
		return (c);
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}
