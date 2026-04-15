/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:06:15 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % ft_lstmap - create new list from applying function to existing list
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	t_list *ft_lstmap(t_list *lst, void *(*f)(void *), 
 * 	                  void (*del)(void *));
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_lstmap() function iterates the list 'lst' and applies the 
 * 	function 'f' to the content of each element. Creates a new list 
 * 	resulting of the successive applications of the function 'f'. The 
 * 	'del' function is used to delete the content of an element if needed.
 * -------------------------------------------------------------------------- *
 * PARAMETERS
 * -------------------------------------------------------------------------- *
 * 	lst: The address of a pointer to an element.
 * 	f: The address of the function used to iterate on the list.
 * 	del: The address of the function used to delete the content of an 
 * 	     element if needed.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The function returns the new list. NULL if the allocation fails.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (new_content == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
