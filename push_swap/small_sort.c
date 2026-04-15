/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:54:19 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 14:54:20 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_index(t_node *stack_a)
{
	int	min;

	min = 2147483647;
	while (stack_a)
	{
		if (stack_a->index < min)
			min = stack_a->index;
		stack_a = stack_a->next;
	}
	return (min);
}

void	rotate_index_a_top(t_node **stack_a, int index)
{
	int	p;
	int	size;
	int	k;

	p = position(*stack_a, index);
	size = node_count(*stack_a);
	if (p == -1)
		return ;
	if (p <= size / 2)
	{
		while (p--)
			ra(stack_a);
	}
	else
	{
		k = size - p;
		while (k--)
			rra(stack_a);
	}
}

void	three_sort(t_node **stack_a)
{
	int	x;
	int	y;
	int	z;

	x = (*stack_a)->index;
	y = (*stack_a)->next->index;
	z = (*stack_a)->next->next->index;
	if (x > y && y < z && x < z)
		sa(stack_a);
	else if (x > y && y > z)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if (x > y && y < z && x > z)
		ra(stack_a);
	else if (x < y && y > z && x < z)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (x < y && y > z && x > z)
		rra(stack_a);
}

void	small_sort(t_node **stack_a, t_node **stack_b, int size)
{
	int	min;

	if (size <= 1)
		return ;
	if (size == 2)
	{
		if ((*stack_a)->index > (*stack_a)->next->index)
			sa(stack_a);
		return ;
	}
	if (size == 3)
	{
		three_sort(stack_a);
		return ;
	}
	while (node_count(*stack_a) > 3)
	{
		min = find_min_index(*stack_a);
		rotate_index_a_top(stack_a, min);
		pb(stack_a, stack_b);
	}
	three_sort(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
}
