/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:42:18 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:43:37 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* % ft_free_split - free memory allocated by ft_split
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 *	The ft_free_split() function frees all memory allocated by ft_split().
 *
 *	It performs the following operations:
 *	1. Frees each individual string in the array
 *	2. Frees the array of pointers itself
 *
 *	The function is safe to call with a NULL pointer.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 *	None (void function).
 * -------------------------------------------------------------------------- *
 */
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
