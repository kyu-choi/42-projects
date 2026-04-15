/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 11:29:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks for parenthesis tokens and creates tokens
 * 
 * @param str Input string
 * @param i Pointer to current index (updated if match)
 * @param head Pointer to token list head
 * @return 1 if parenthesis found and added, 0 otherwise
 */
int	check_parenthesis_token(char *str, int *i, t_token **head)
{
	t_token	*token;

	if (str[*i] == '(')
	{
		token = create_token(TOKEN_LPAREN, ft_strdup("("));
		if (!token)
			return (0);
		add_token_to_list_util(head, token);
		(*i)++;
		return (1);
	}
	if (str[*i] == ')')
	{
		token = create_token(TOKEN_RPAREN, ft_strdup(")"));
		if (!token)
			return (0);
		add_token_to_list_util(head, token);
		(*i)++;
		return (1);
	}
	return (0);
}

/**
 * @brief Checks if parentheses are properly balanced
 * 
 * @param tokens Token list
 * @return int 0 on success, -1 if unmatched
 */
static int	check_parenthesis_balance(t_token *tokens)
{
	int		depth;
	t_token	*current;

	depth = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			depth++;
		else if (current->type == TOKEN_RPAREN)
		{
			depth--;
			if (depth < 0)
				return (-1);
		}
		current = current->next;
	}
	if (depth != 0)
		return (-1);
	return (0);
}

/**
 * @brief Extracts token group enclosed in parentheses
 * 
 * @param start Start token (LPAREN)
 * @param end Pointer to token after RPAREN
 * @return t_token* First token inside parentheses
 */
static t_token	*extract_parenthesis_group(t_token *start, t_token **end)
{
	int		depth;
	t_token	*current;
	t_token	*group_start;

	if (!start || start->type != TOKEN_LPAREN)
		return (NULL);
	depth = 1;
	current = start->next;
	group_start = current;
	while (current && depth > 0)
	{
		if (current->type == TOKEN_LPAREN)
			depth++;
		else if (current->type == TOKEN_RPAREN)
		{
			depth--;
			if (depth == 0)
			{
				*end = current->next;
				return (group_start);
			}
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Checks if token list contains parentheses
 * 
 * @param tokens Token list to check
 * @return int 1 if contains parentheses, 0 otherwise
 */
int	has_parenthesis(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_LPAREN || current->type == TOKEN_RPAREN)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Validates parenthesis syntax (proper pairs, no empty groups)
 * 
 * @param tokens Token list to validate
 * @return int 0 on success, -1 on error
 */
int	validate_parenthesis(t_token *tokens)
{
	t_token	*current;
	t_token	*end;

	if (check_parenthesis_balance(tokens) != 0)
	{
		print_unmatched_paren_error_bonus();
		return (-1);
	}
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
		{
			end = NULL;
			if (!extract_parenthesis_group(current, &end) || !end)
			{
				print_empty_paren_error_bonus();
				return (-1);
			}
			current = end;
		}
		else
			current = current->next;
	}
	return (0);
}
