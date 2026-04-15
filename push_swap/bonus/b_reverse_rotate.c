/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:30:51 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/08 13:30:52 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	b_reverse_rotate(t_node **stack)
{
	t_node	*first;
	t_node	*pre;
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	pre = *stack;
	last = *stack;
	while (last->next)
	{
		pre = last;
		last = last->next;
	}
	last->next = first;
	*stack = last;
	pre->next = NULL;
}

void	b_rra(t_node **stack_a)
{
	b_reverse_rotate(stack_a);
}

void	b_rrb(t_node **stack_b)
{
	b_reverse_rotate(stack_b);
}

void	b_rrr(t_node **stack_a, t_node **stack_b)
{
	b_reverse_rotate(stack_a);
	b_reverse_rotate(stack_b);
}
