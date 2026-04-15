/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:03:56 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/07/21 18:06:50 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}	t_node;

typedef struct s_context
{
	int	win;
	int	next;
	int	total;
}	t_context;

t_node	*make_stack(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	node_append(t_node **stack_a, int val);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

void	check_stack(t_node *stack_a);

void	sort_index(t_node **stack_a);
void	find_win(t_node **stack, t_context *context);

void	small_sort(t_node **stack_a, t_node **stack_b, int size);

void	rotate_push(t_node **stack_a, t_node **stack_b, t_context *context);

void	find_b_insert_a(t_node **stack_a, t_node **stack_b, int total);
int		position(t_node *stack, int target);

int		node_count(t_node *stack);

void	pa(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);

void	swap(t_node **stack);
void	ss(t_node **stack_a, t_node **stack_b);
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);

void	rotate(t_node **stack);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);

void	reverse_rotate(t_node **stack);
void	rra(t_node **stack_a);
void	rrb(t_node **stack_b);
void	rrr(t_node **stack_a, t_node **stack_b);

void	b_pa(t_node **stack_a, t_node **stack_b);
void	b_pb(t_node **stack_a, t_node **stack_b);

void	b_swap(t_node **stack);
void	b_ss(t_node **stack_a, t_node **stack_b);
void	b_sa(t_node **stack_a);
void	b_sb(t_node **stack_b);

void	b_rotate(t_node **stack);
void	b_ra(t_node **stack_a);
void	b_rb(t_node **stack_b);
void	b_rr(t_node **stack_a, t_node **stack_b);

void	b_reverse_rotate(t_node **stack);
void	b_rra(t_node **stack_a);
void	b_rrb(t_node **stack_b);
void	b_rrr(t_node **stack_a, t_node **stack_b);

void	checking(t_node **stack_a, t_node **stack_b);
int		is_sorted(t_node *stack_a);
void	free_stack(t_node **stack);

void	free_stack_src_exit(t_node **stack, char **src);
void	free_src(char **src);
void	free_stack_error_exit(t_node **stack);
void	free_all(t_node **stack_a, t_node **stack_b);
void	free_stack(t_node **stack);

#endif
