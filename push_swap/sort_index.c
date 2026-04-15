/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:57:51 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/08 11:57:52 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_value(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	selection_sort(int *arr, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (arr[i] > arr[j])
				swap_value(&arr[i], &arr[j]);
			j++;
		}
		i++;
	}
}

void	index_node(t_node **stack_a, int *arr, int count)
{
	int		i;
	t_node	*cur;

	i = 0;
	while (i < count)
	{
		cur = *stack_a;
		while (cur)
		{
			if (cur->value == arr[i])
				cur->index = i;
			cur = cur->next;
		}
		i++;
	}
}

void	make_arr(t_node **stack_a, int *arr, int count)
{
	t_node	*cur;
	int		i;

	cur = *stack_a;
	i = 0;
	while (cur)
	{
		arr[i] = cur->value;
		i++;
		cur = cur->next;
	}
	selection_sort(arr, count);
}

void	sort_index(t_node **stack_a)
{
	t_node	*test;
	int		count;
	int		*arr;

	if (!stack_a || !*stack_a)
	{
		write(1, "error\n", 6);
		free_stack(stack_a);
		exit(1);
	}
	test = *stack_a;
	count = 0;
	while (test)
	{
		count++;
		test = test->next;
	}
	arr = (int *)malloc(sizeof(int) * count);
	make_arr(stack_a, arr, count);
	index_node(stack_a, arr, count);
	free(arr);
}
