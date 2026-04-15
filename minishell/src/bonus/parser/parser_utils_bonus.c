/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 12:25:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
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
	cmd->is_background = 0;
	cmd->is_subshell = 0;
	cmd->subshell_tokens = NULL;
	cmd->next = NULL;
	return (cmd);
}

/**
 * @brief Checks if token list ends with a trailing operator
 * @param tokens Token list to check
 * @return 1 if ends with pipe/and/or (binary operators), 0 otherwise
 * @details Used to detect incomplete commands needing continuation.
 *          Only BINARY operators (|, &&, ||) are trailing operators.
 *          TERMINATORS like semicolon (;) and background (&) end commands,
 *          so they do NOT require continuation.
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
