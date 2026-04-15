/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:16:48 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/07 11:16:49 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	val_atoi(t_node **stack_a, char *sor)
{
	int	res;

	res = ft_atoi(sor);
	if (res == 0 && (ft_strncmp(sor, "0", 1) != 0))
		return (-1);
	node_append(stack_a, res);
	return (res);
}

t_node	**moreargv(char **src, t_node **stack_a)
{
	int	i[2];

	i[0] = 1;
	while (src[i[0]])
	{
		i[1] = 0;
		while (src[i[0]][i[1]])
		{
			if (i[1] == 0)
			{
				if (src[i[0]][i[1]] == '+' || src[i[0]][i[1]] == '-')
				{
					i[1]++;
					continue ;
				}
			}
			if (src[i[0]][i[1]] < '0' || src[i[0]][i[1]] > '9')
				free_stack_error_exit(stack_a);
			i[1]++;
		}
		if (val_atoi(stack_a, src[i[0]]) == -1)
			free_stack_error_exit(stack_a);
		i[0]++;
	}
	return (stack_a);
}

t_node	**oneargv(t_node **stack_a, char **src)
{
	int	i[2];

	i[0] = 0;
	while (src[i[0]])
	{
		i[1] = 0;
		while (src[i[0]][i[1]])
		{
			if (i[1] == 0)
			{
				if (src[i[0]][i[1]] == '+' || src[i[0]][i[1]] == '-')
				{
					i[1]++;
					continue ;
				}
			}
			if (src[i[0]][i[1]] < '0' || src[i[0]][i[1]] > '9')
				free_stack_src_exit(stack_a, src);
			i[1]++;
		}
		if (val_atoi(stack_a, src[i[0]]) == -1)
			free_stack_src_exit(stack_a, src);
		i[0]++;
	}
	return (stack_a);
}

void	argc_check(int argc, char **argv, t_node **stack_a)
{
	char	**src;

	if (argc == 1)
		exit(0);
	else if (argc == 2)
	{
		src = ft_split(argv[1], ' ');
		stack_a = oneargv(stack_a, src);
		free_src(src);
	}
	else
		stack_a = moreargv(argv, stack_a);
}

t_node	*make_stack(int argc, char **argv)
{
	t_node	*stack_a;

	stack_a = NULL;
	argc_check(argc, argv, &stack_a);
	check_stack(stack_a);
	return (stack_a);
}
