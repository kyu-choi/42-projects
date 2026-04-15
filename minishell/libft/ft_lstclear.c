/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:05:09 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % ft_lstclear - delete and free all elements of a list
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	void ft_lstclear(t_list **lst, void (*del)(void *));
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_lstclear() function deletes and frees the given element and 
 * 	every successor of that element, using the function 'del' and free(3).
 * 	Finally, the pointer to the list must be set to NULL.
 * -------------------------------------------------------------------------- *
 * PARAMETERS
 * -------------------------------------------------------------------------- *
 * 	lst: The address of a pointer to an element.
 * 	del: The address of the function used to delete the content of the 
 * 	     element.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_lst;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		next_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_lst;
	}
	*lst = NULL;
}
