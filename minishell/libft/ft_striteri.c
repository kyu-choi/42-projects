/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <ialskdji@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:32:45 by hyeonwki          #+#    #+#             */
/*   Updated: 2024/12/06 21:19:41 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % Function: ft_striteri - Iterate over a string and apply a function to 
 * 	each character
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	void ft_striteri(char *s, void (*f)(unsigned int, char*));
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_striteri() function applies the function 'f' to each character 
 * 	of the string 's', passing its index as the first argument. Each 
 * 	character is passed by address to 'f' to be modified if necessary. If 
 * 	's' is NULL, the function does nothing.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	None.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		++i;
	}
}
