/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:28:17 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/01 16:33:11 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % man isalpha
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	#include <ctype.h>
 *
 * 	int	isalpha(int c);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	isalpha() checks for an alphabetic character; in the standard "C" 
 * 	locale, it is equivalent to (isupper(c) || islower(c)).	In some 
 * 	locales, there may be additional characters for which isalpha() is 
 * 	true—letters which are neither uppercase nor lowercase.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *      The value returned is a non-zero value if the letter c belongs to the
 * 	tested class, otherwise it is zero.
 * -------------------------------------------------------------------------- *
 */

int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (0x0010);
	if (c >= 'a' && c <= 'z')
		return (0x0008);
	return (0);
}
