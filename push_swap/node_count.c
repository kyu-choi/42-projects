/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:53:57 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 14:53:58 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	node_count(t_node *stack)
{
	t_node	*cur;
	int		count;

	if (!stack)
		return (0);
	cur = stack;
	count = 1;
	while (cur->next)
	{
		cur = cur->next;
		count++;
	}
	return (count);
}
