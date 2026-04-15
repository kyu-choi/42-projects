/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_full_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 22:06:36 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks for empty parenthesis pairs
 * @param tok Token to check
 * @param shell Shell state for error reporting
 * @return 1 if empty parenthesis found, 0 otherwise
 */
int		check_empty_paren(t_token *tok, t_shell *shell);

/**
 * @brief Checks if token type is an operator
 * @param type Token type to check
 * @return 1 if operator (pipe, and, or, semicolon, background), 0 otherwise
 */
int		is_operator_token(t_token_type type);

/**
 * @brief Finds matching right parenthesis for left parenthesis
 * @param tok Starting left parenthesis token
 * @return Matching right parenthesis token, or NULL if not found
 */
t_token	*find_matching_rparen(t_token *tok);

/**
 * @brief Checks for right parenthesis syntax errors
 * @param tokens Token list to check
 * @param shell Shell state for error reporting
 * @param depth Current parenthesis nesting depth
 * @return 1 if error found, 0 otherwise
 */
int		check_rparen_error(t_token *tokens, t_shell *shell, int depth);

/**
 * @brief Checks if command starts with invalid token
 * @param tokens Token list to check
 * @param shell Shell state for error reporting
 * @return 1 if invalid start found, 0 otherwise
 */
int		check_invalid_start(t_token *tokens, t_shell *shell);

/**
 * @brief Checks for operator syntax errors during parsing
 * @param tokens Token list to check
 * @param shell Shell state for error reporting
 * @param head Parsed command list head
 * @return 1 if error found, 0 otherwise
 */
int		check_parse_operator_error(t_token *tokens, t_shell *shell,
			t_cmd *head);

/**
 * @brief Validates a newly parsed command structure
 * @param new_cmd Command to validate
 * @param shell Shell state for error reporting
 * @param head Command list head
 * @return 1 if valid, 0 if invalid
 */
int		validate_parsed_cmd(t_cmd *new_cmd, t_shell *shell, t_cmd *head);

/**
 * @brief Validates parenthesis balance and syntax
 * @param tokens Token list to validate
 * @param shell Shell state for error reporting
 * @return 1 if error found, 0 otherwise
 */
static int	validate_parenthesis(t_token *tokens, t_shell *shell)
{
	int		depth;

	depth = 0;
	while (tokens)
	{
		if (check_empty_paren(tokens, shell))
			return (1);
		if (tokens->type == TOKEN_LPAREN)
			depth++;
		else if (tokens->type == TOKEN_RPAREN)
		{
			depth--;
			if (check_rparen_error(tokens, shell, depth))
				return (1);
		}
		tokens = tokens->next;
	}
	if (depth != 0)
	{
		print_unmatched_paren_error_bonus();
		shell->parse_error_type = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Handles operator tokens during parsing
 * @param tokens Pointer to current token (updated)
 * @param current Current command
 */
static void	handle_operator_token(t_token **tokens, t_cmd *current)
{
	if ((*tokens)->type == TOKEN_BACKGROUND)
	{
		current->is_background = 1;
		current->operator = TOKEN_END;
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)
	{
		current->operator = (*tokens)->type;
		*tokens = (*tokens)->next;
	}
	else
	{
		current->operator = TOKEN_PIPE;
		*tokens = (*tokens)->next;
	}
}

/**
 * @brief Processes next command in pipeline
 * @param tokens Pointer to token stream
 * @param shell Shell state
 * @param head Head of command list (for cleanup on error)
 * @return New command or NULL on error
 */
static t_cmd	*process_next_cmd(t_token **tokens, t_shell *shell, t_cmd *head)
{
	t_cmd	*new_cmd;

	if (check_invalid_start(*tokens, shell))
	{
		free_cmds(head);
		return (NULL);
	}
	new_cmd = parse_one_cmd(tokens, shell);
	if (!new_cmd)
	{
		write(2, "minishell: syntax error near unexpected token\n", 47);
		shell->parse_error_type = 2;
		free_cmds(head);
		return (NULL);
	}
	if (!validate_parsed_cmd(new_cmd, shell, head))
		return (NULL);
	return (new_cmd);
}

/**
 * @brief Parses token list into command pipeline
 * @param tokens Token list from tokenizer
 * @param shell Shell state for variable expansion
 * @return Head of command pipeline linked list
 * @details Splits pipeline on PIPE tokens, handles multiple commands
 */
t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*current;

	if (!tokens || validate_parenthesis(tokens, shell)
		|| check_invalid_start(tokens, shell))
		return (NULL);
	head = parse_one_cmd(&tokens, shell);
	if (!head)
		return (NULL);
	current = head;
	while (tokens && (tokens->type == TOKEN_PIPE
			|| tokens->type == TOKEN_AND || tokens->type == TOKEN_OR
			|| tokens->type == TOKEN_BACKGROUND))
	{
		handle_operator_token(&tokens, current);
		if (current->is_background)
			break ;
		if (check_parse_operator_error(tokens, shell, head))
			return (NULL);
		current->next = process_next_cmd(&tokens, shell, head);
		if (!current->next)
			return (NULL);
		current = current->next;
	}
	return (head);
}

/**
 * @brief Frees entire command pipeline
 * @param cmds Head of command linked list
 * @details Frees args array, redirections, subshell tokens, and command nodes
 */
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		i = 0;
		while (tmp->args && tmp->args[i])
			free(tmp->args[i++]);
		if (tmp->args)
			free(tmp->args);
		free_cmd_redirs(tmp->redirs);
		if (tmp->subshell_tokens)
			free_tokens(tmp->subshell_tokens);
		free(tmp);
	}
}
