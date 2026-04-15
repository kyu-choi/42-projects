/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:54:49 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/29 14:54:50 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	three_check(t_node **stack_a, t_node **stack_b, char *line)
{
	if (ft_strncmp(line, "ss\n", 3) == 0)
		b_ss(stack_a, stack_b);
	else if (ft_strncmp(line, "sa\n", 3) == 0)
		b_sa(stack_a);
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		b_sb(stack_b);
	else if (ft_strncmp(line, "rr\n", 3) == 0)
		b_rr(stack_a, stack_b);
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		b_ra(stack_a);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		b_rb(stack_b);
	else if (ft_strncmp(line, "pa\n", 3) == 0)
		b_pa(stack_a, stack_b);
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		b_pb(stack_a, stack_b);
	else
		return (-1);
	return (0);
}

int	four_check(t_node **stack_a, t_node **stack_b, char *line)
{
	if (ft_strncmp(line, "rra\n", 4) == 0)
		b_rra(stack_a);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		b_rrb(stack_b);
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
		b_rrr(stack_a, stack_b);
	else
		return (-1);
	return (0);
}

int	apply_line(t_node **stack_a, t_node **stack_b, char *line)
{
	int	size;
	int	val;

	size = ft_strlen(line);
	if (size == 3)
		val = three_check(stack_a, stack_b, line);
	else if (size == 4)
		val = four_check(stack_a, stack_b, line);
	else
	{
		write(1, "error\n", 6);
		return (-1);
	}
	if (val == -1)
	{
		write(1, "error\n", 6);
		return (-1);
	}
	return (0);
}

void	checking(t_node **stack_a, t_node **stack_b)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		if (apply_line(stack_a, stack_b, line) == -1)
		{
			free(line);
			free_stack(stack_a);
			free_stack(stack_b);
			exit(1);
		}
		free(line);
		line = get_next_line(0);
	}
}
