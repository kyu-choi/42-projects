/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/03 15:27:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks for logical operators (&&, ||, &)
 * @param str Input string
 * @param i Pointer to current index (updated if match)
 * @param head Pointer to token list head
 * @return 1 if operator found and added, 0 otherwise
 * @details Handles && (AND), || (OR), and & (BACKGROUND) operators
 */
int	check_logical_operator(char *str, int *i, t_token **head)
{
	if (str[*i] == '&' && str[*i + 1] == '&')
	{
		add_token_to_list_util(head, create_token(TOKEN_AND,
				ft_strdup("&&")));
		*i += 2;
		return (1);
	}
	if (str[*i] == '&' && !ft_isdigit(str[*i + 1]))
	{
		add_token_to_list_util(head, create_token(TOKEN_BACKGROUND,
				ft_strdup("&")));
		*i += 1;
		return (1);
	}
	if (str[*i] == '|' && str[*i + 1] == '|')
	{
		add_token_to_list_util(head, create_token(TOKEN_OR,
				ft_strdup("||")));
		*i += 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Determines if next command should execute based on operator
 * @param operator Operator type (TOKEN_AND or TOKEN_OR)
 * @param last_status Exit status of previous command
 * @return 1 if should execute, 0 if should skip
 */
static int	should_execute_next(t_token_type operator, int last_status)
{
	if (operator == TOKEN_AND)
		return (last_status == 0);
	if (operator == TOKEN_OR)
		return (last_status != 0);
	return (1);
}

/**
 * @brief Skips a pipeline group without execution
 * @param start First command in pipeline
 * @param end Pointer to store next command after pipeline
 * @param operator_out Pointer to store the operator after the pipeline
 */
static void	skip_pipeline_group(t_cmd *start, t_cmd **end,
		t_token_type *operator_out)
{
	t_cmd	*pipeline_end;

	pipeline_end = start;
	while (pipeline_end->next && pipeline_end->operator == TOKEN_PIPE)
		pipeline_end = pipeline_end->next;
	*end = pipeline_end->next;
	*operator_out = pipeline_end->operator;
}

/**
 * @brief Executes a pipeline group (commands connected with |)
 * @param shell Shell state with environment
 * @param start First command in pipeline
 * @param end Pointer to store next command after pipeline
 * @param operator_out Pointer to store the operator after the pipeline
 * @return Exit status of pipeline
 */
static int	execute_pipeline_group(t_shell *shell, t_cmd *start, t_cmd **end,
		t_token_type *operator_out)
{
	t_cmd	*pipeline_end;
	int		status;

	pipeline_end = start;
	while (pipeline_end->next && pipeline_end->operator == TOKEN_PIPE)
		pipeline_end = pipeline_end->next;
	*end = pipeline_end->next;
	*operator_out = pipeline_end->operator;
	if (pipeline_end == start)
		return (execute_simple_cmd(shell, start));
	pipeline_end->next = NULL;
	status = execute(shell, start);
	pipeline_end->next = *end;
	return (status);
}

/**
 * @brief Executes command pipeline with && || operators
 * @param shell Shell state with environment
 * @param cmds Command pipeline with operators
 * @return Exit status of last executed command
 * @details Implements short-circuit evaluation for && and ||
 */
int	execute_with_operators(t_shell *shell, t_cmd *cmds)
{
	t_cmd			*current;
	t_cmd			*next;
	t_token_type	op;
	int				status;

	if (!cmds)
		return (0);
	current = cmds;
	status = execute_pipeline_group(shell, current, &next, &op);
	while (next)
	{
		if (!should_execute_next(op, status))
		{
			current = next;
			skip_pipeline_group(current, &next, &op);
			continue ;
		}
		current = next;
		status = execute_pipeline_group(shell, current, &next, &op);
	}
	return (status);
}
