/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:41:15 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/01 17:52:14 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man tolower - convert uppercase to lowercase
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 *      #include <ctype.h>
 *
 *	int	tolower(int c);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	This function convert uppercase letters to lowercase, and vice versa.
 * 
 * 	If c is an uppercase letter, tolower() returns its lowercase 
 * 	equivalent, if a lowercase representation exists in the current 
 * 	locale. Otherwise, it returns c.
 *
 * 	If c is neither an unsigned char value nor EOF, the behavior of these 
 * 	functions is undefined.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The value returned is the lowercase equivalent of 'c' if it exists, 
 * 	or 'c' unchanged if no conversion was performed.
 * -------------------------------------------------------------------------- *
 */

#include <stdio.h>
#include <limits.h>

int	ft_tolower(int c)
{
	if (c == EOF)
		return (EOF);
	if (c < 0 || c > UCHAR_MAX)
		return (c);
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}
