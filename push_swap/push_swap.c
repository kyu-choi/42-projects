/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:14:11 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/07 11:14:13 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node		*stack_a;
	t_node		*stack_b;
	t_context	context;

	stack_a = make_stack(argc, argv);
	stack_b = NULL;
	sort_index(&stack_a);
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	find_win(&stack_a, &context);
	if (context.total <= 5)
	{
		small_sort(&stack_a, &stack_b, context.total);
		free_all(&stack_a, &stack_b);
		return (0);
	}
	rotate_push(&stack_a, &stack_b, &context);
	find_b_insert_a(&stack_a, &stack_b, context.total);
	free_all(&stack_a, &stack_b);
	return (0);
}
