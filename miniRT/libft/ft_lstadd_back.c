/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:04:24 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/16 13:20:36 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % ft_lstadd_back - add new element at end of list
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	void ft_lstadd_back(t_list **lst, t_list *new);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_lstadd_back() function adds the element 'new' at the end of 
 * 	the list pointed to by 'lst'. If the list is empty, the new element 
 * 	becomes the head of the list.
 * -------------------------------------------------------------------------- *
 * PARAMETERS
 * -------------------------------------------------------------------------- *
 * 	lst: The address of a pointer to the first link of a list.
 * 	new: The address of a pointer to the element to be added to the list.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new_node;
	else
		*lst = new_node;
}
