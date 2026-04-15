/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:03:12 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/16 13:20:33 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % ft_lstadd_front - add new element at beginning of list
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	void ft_lstadd_front(t_list **lst, t_list *new);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_lstadd_front() function adds the element 'new' at the beginning 
 * 	of the list pointed to by 'lst'. The pointer to the head of the list 
 * 	is updated to point to the new element.
 * -------------------------------------------------------------------------- *
 * PARAMETERS
 * -------------------------------------------------------------------------- *
 * 	lst: The address of a pointer to the first link of a list.
 * 	new: The address of a pointer to the element to be added to the list.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst)
		new_node->next = *lst;
	*lst = new_node;
}
