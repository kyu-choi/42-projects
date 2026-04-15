/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:30:09 by hyeonwki          #+#    #+#             */
/*   Updated: 2026/02/15 22:30:09 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* % ft_streq - check whether two strings are exactly equal
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *	The ft_streq() function compares two null-terminated strings.
 *	If both strings have the same length and same content, it returns 1.
 *	If either pointer is NULL or content differs, it returns 0.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *	Returns 1 if equal, 0 otherwise.
 * -------------------------------------------------------------------------- *
 */
int	ft_streq(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	while (*a && *b)
	{
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
	if (*a != *b)
		return (0);
	return (1);
}
