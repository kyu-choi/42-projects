/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:44:19 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:19 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*node_new(int val)
{
	t_node	*res;

	res = (t_node *)malloc(sizeof(t_node) * 1);
	if (!res)
		return (NULL);
	res->value = val;
	res->index = -1;
	res->next = NULL;
	return (res);
}

void	node_append(t_node **stack_a, int val)
{
	t_node	*new;
	t_node	*cur;

	new = node_new(val);
	if (!*stack_a)
	{
		*stack_a = new;
		return ;
	}
	cur = *stack_a;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
