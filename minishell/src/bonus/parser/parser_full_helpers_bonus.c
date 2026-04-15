/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_full_helpers_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 11:29:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_bonus.h"

/**
 * @brief Checks if token type is an operator
 * @param type Token type to check
 * @return 1 if operator, 0 otherwise
 */
int	is_operator_token(t_token_type type);

/**
 * @brief Checks for errors after right parenthesis
 * @param tokens Current token (at RPAREN)
 * @param shell Shell state for error reporting
 * @param depth Current parenthesis nesting depth
 * @return 1 if error found, 0 otherwise
 */
int	check_rparen_error(t_token *tokens, t_shell *shell, int depth)
{
	if (depth < 0)
	{
		print_syntax_error_bonus(")");
		shell->parse_error_type = 2;
		return (1);
	}
	if (tokens->next && tokens->next->type == TOKEN_LPAREN)
	{
		print_syntax_error_bonus("(");
		shell->parse_error_type = 2;
		return (1);
	}
	if (tokens->next && tokens->next->type != TOKEN_RPAREN
		&& !is_operator_token(tokens->next->type))
	{
		print_syntax_error_bonus(tokens->next->value);
		shell->parse_error_type = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Checks for invalid starting token
 * @param tokens Token list
 * @param shell Shell state for error reporting
 * @return 1 if invalid start, 0 otherwise
 */
int	check_invalid_start(t_token *tokens, t_shell *shell)
{
	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_LPAREN)
		return (0);
	if (is_invalid_token(tokens))
	{
		print_syntax_error_bonus(tokens->value);
		shell->parse_error_type = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Checks for operator-related syntax errors during parsing
 * @param tokens Current token position
 * @param shell Shell state for error reporting
 * @param head Command list to free on error
 * @return 1 if error found, 0 otherwise
 */
int	check_parse_operator_error(t_token *tokens, t_shell *shell, t_cmd *head)
{
	if (!tokens)
	{
		print_syntax_error_bonus(NULL);
		shell->parse_error_type = 2;
		free_cmds(head);
		return (1);
	}
	if (tokens->type == TOKEN_PIPE)
	{
		print_syntax_error_bonus("|");
		shell->parse_error_type = 2;
		free_cmds(head);
		return (1);
	}
	return (0);
}

/**
 * @brief Validates a parsed command structure for completeness
 * @param new_cmd Newly parsed command
 * @param shell Shell state for error reporting
 * @param head Command list to free on error
 * @return 1 if valid, 0 if invalid
 */
int	validate_parsed_cmd(t_cmd *new_cmd, t_shell *shell, t_cmd *head)
{
	if (!new_cmd->is_subshell && !new_cmd->args)
	{
		print_syntax_error_bonus(NULL);
		shell->parse_error_type = 2;
		free_cmds(head);
		free_cmds(new_cmd);
		return (0);
	}
	if (!new_cmd->is_subshell && !new_cmd->args[0] && !new_cmd->redirs)
	{
		print_syntax_error_bonus(NULL);
		shell->parse_error_type = 2;
		free_cmds(head);
		free_cmds(new_cmd);
		return (0);
	}
	return (1);
}
