/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:26:20 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/08 13:26:21 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	b_swap(t_node **stack)
{
	t_node	*node1;
	t_node	*node2;

	if (!*stack || !(*stack)->next)
		return ;
	node1 = *stack;
	node2 = node1->next;
	node1->next = node2->next;
	node2->next = node1;
	*stack = node2;
}

void	b_ss(t_node **stack_a, t_node **stack_b)
{
	swap(stack_a);
	swap(stack_b);
}

void	b_sa(t_node **stack_a)
{
	swap(stack_a);
}

void	b_sb(t_node **stack_b)
{
	swap(stack_b);
}
