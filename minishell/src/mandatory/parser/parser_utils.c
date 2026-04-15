/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 12:25:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Creates empty command structure
 * @return Newly allocated command with NULL fields
 * @details Initializes args, redirs, next to NULL
 */
t_cmd	*create_cmd_util(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

/**
 * @brief Parses next command in pipeline
 * @param tokens Pointer to current token
 * @param current Current command
 * @param shell Shell state
 * @return New command or NULL on error
 */
t_cmd	*parse_next_cmd_util(t_token **tokens, t_cmd *current, t_shell *shell)
{
	t_cmd	*new_cmd;

	if ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR)
		current->operator = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens)
	{
		print_syntax_error("newline");
		shell->parse_error_type = 2;
		return (NULL);
	}
	if ((*tokens)->type == TOKEN_PIPE)
	{
		print_syntax_error("|");
		shell->parse_error_type = 2;
		return (NULL);
	}
	new_cmd = parse_one_cmd(tokens, shell);
	return (new_cmd);
}

/**
 * @brief Checks if token list ends with a trailing operator
 * @param tokens Token list to check
 * @return 1 if ends with pipe/and/or, 0 otherwise
 * @details Used to detect incomplete commands needing continuation
 */
int	has_trailing_operator(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (0);
	current = tokens;
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE)
		return (1);
	if (current->type == TOKEN_AND)
		return (1);
	if (current->type == TOKEN_OR)
		return (1);
	return (0);
}

/**
 * @brief Processes token value (expansion + quote removal)
 * @param value Token value to process
 * @param shell Shell state for variable expansion
 * @return Newly allocated processed string
 * @details First expands variables, then removes quotes
 */
char	*process_token_value_util(char *value, t_shell *shell)
{
	char	*expanded;

	expanded = expand_variables(value, shell);
	return (expanded);
}
