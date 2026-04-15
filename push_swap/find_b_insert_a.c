/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_b_insert_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:53:34 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 14:53:36 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	position(t_node *stack, int target)
{
	int	i;

	i = 0;
	while (stack)
	{
		if (stack->index == target)
			return (i);
		stack = stack->next;
		i++;
	}
	return (-1);
}

void	rotate_b_top(t_node **stack_b, int target)
{
	int	p;
	int	size;
	int	k;

	p = position(*stack_b, target);
	size = node_count(*stack_b);
	if (p == -1)
		return ;
	if (p <= size / 2)
		while (p--)
			rb(stack_b);
	else
	{
		k = size - p;
		while (k--)
			rrb(stack_b);
	}
}

void	find_b_insert_a(t_node **stack_a, t_node **stack_b, int total)
{
	int	n;

	n = total - 1;
	while (*stack_b)
	{
		rotate_b_top(stack_b, n);
		pa(stack_a, stack_b);
		n--;
	}
}
