/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:04:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/08/05 20:54:35 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* % ft_lstlast - returns the last element of the list
 * -------------------------------------------------------------------------- *
 * SYNOPSIS
 * -------------------------------------------------------------------------- *
 * 	t_list *ft_lstlast(t_list *lst);
 * -------------------------------------------------------------------------- *
 * DESCRIPTION
 * -------------------------------------------------------------------------- *
 * 	The ft_lstlast() function returns the last element of the list 'lst'.
 * 	It traverses the list from the beginning until it finds a node whose 
 * 	'next' pointer is NULL.
 * -------------------------------------------------------------------------- *
 * RETURN VALUE
 * -------------------------------------------------------------------------- *
 * 	The function returns a pointer to the last element of the list.
 * 	If the list is empty (lst is NULL), it returns NULL.
 * -------------------------------------------------------------------------- *
 */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
