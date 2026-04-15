/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:53:50 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 14:53:51 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_win(t_node **stack, t_context *context)
{
	int	size;

	size = node_count(*stack);
	context->total = size;
	if (size <= 100)
		context->win = 20;
	else if (size < 500)
		context->win = 30;
	else if (size >= 500)
		context->win = 40;
	context->next = 0;
}
