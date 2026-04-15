/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:05:44 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % ft_lstiter - apply function to content of all list elements
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	void ft_lstiter(t_list *lst, void (*f)(void *));
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_lstiter() function iterates the list 'lst' and applies the 
 * 	function 'f' to the content of each element. The function 'f' is 
 * 	called with the content of each node as its parameter.
 * -------------------------------------------------------------------------- *
 * PARAMETERS
 * -------------------------------------------------------------------------- *
 * 	lst: The address of a pointer to an element.
 * 	f: The address of the function used to iterate on the list.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f((void *)(lst->content));
		lst = lst->next;
	}
}
