/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:44:15 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/07/24 14:44:18 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_node **stack)
{
	t_node	*cur;

	cur = *stack;
	write(1, "\n", 1);
	while (cur)
	{
		ft_printf("%d\n", cur->value);
		cur = cur->next;
	}
}

void	print_index(t_node **stack)
{
	t_node	*cur;

	cur = *stack;
	write(1, "\n", 1);
	while (cur)
	{
		ft_printf("%d\n", cur->index);
		cur = cur->next;
	}
}
