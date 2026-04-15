/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:54:12 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 14:54:14 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_push(t_node **stack_a, t_node **stack_b, t_context *context)
{
	while (*stack_a)
	{
		if ((*stack_a)->index < context->next)
		{
			pb(stack_a, stack_b);
			rb(stack_b);
			context->next++;
		}
		else if ((*stack_a)->index < context->next + \
		context->win && (*stack_a)->index >= context->next)
		{
			pb(stack_a, stack_b);
			context->next++;
		}
		else
			ra(stack_a);
	}
}
