/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:28:17 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 16:28:18 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack_src_exit(t_node **stack, char **src)
{
	int	i;

	free_stack(stack);
	i = 0;
	if (!src)
		return ;
	while (src[i])
	{
		free(src[i]);
		i++;
	}
	free(src);
	ft_printf("error\n");
	exit(1);
}

void	free_src(char **src)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (src[i])
	{
		free(src[i]);
		i++;
	}
	free(src);
}

void	free_stack_error_exit(t_node **stack)
{
	free_stack(stack);
	ft_printf("error\n");
	exit(1);
}

void	free_all(t_node **stack_a, t_node **stack_b)
{
	if (stack_a)
		free_stack(stack_a);
	if (stack_b)
		free_stack(stack_b);
}

void	free_stack(t_node **stack)
{
	t_node	*cur;
	t_node	*next;

	if (!stack || !*stack)
		return ;
	cur = *stack;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	*stack = NULL;
}
