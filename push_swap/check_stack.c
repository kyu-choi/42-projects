/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:34:20 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/31 17:34:22 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_stack(t_node *stack_a)
{
	t_node	*cur;
	t_node	*cmp;

	cur = stack_a;
	while (cur != NULL)
	{
		cmp = cur->next;
		while (cmp != NULL)
		{
			if (cur->value == cmp->value)
				free_stack_error_exit(&stack_a);
			cmp = cmp->next;
		}
		cur = cur->next;
	}
}
