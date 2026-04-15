/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Copies a range of tokens from start to end
 * @param start Starting token
 * @param end Ending token (exclusive)
 * @return New token list containing copied range
 */
t_token	*copy_token_range(t_token *start, t_token *end);

/**
 * @brief Handles parsing of subshell commands
 * @param tokens Pointer to token list
 * @param cmd Command structure to populate
 * @return Next token after subshell
 */
t_token	*handle_subshell_cmd(t_token **tokens, t_cmd *cmd);

/**
 * @brief Allocates and initializes command arguments array
 * @param cmd Command structure
 * @param tokens Token list to process
 * @return 1 on success, 0 on failure
 */
int		allocate_cmd_args(t_cmd *cmd, t_token *tokens);

/**
 * @brief Checks if token is an invalid operator at current position
 * @param tokens Token to check
 * @return 1 if invalid (operators, &, ;), 0 otherwise
 */
int	is_invalid_token(t_token *tokens)
{
	if (tokens->type == TOKEN_AND || tokens->type == TOKEN_OR
		|| tokens->type == TOKEN_PIPE || tokens->type == TOKEN_BACKGROUND)
		return (1);
	if (tokens->type == TOKEN_WORD && tokens->value
		&& tokens->value[0] == '&' && !tokens->value[1])
		return (1);
	if (tokens->type == TOKEN_WORD && tokens->value
		&& tokens->value[0] == ';' && !tokens->value[1])
		return (1);
	return (0);
}

/**
 * @brief Parses one command from token stream
 * @param tokens Pointer to token stream (updated after parse)
 * @param shell Shell state for variable expansion
 * @return Newly allocated command structure
 * @details Allocates args array, processes redirections and arguments
 */
t_cmd	*parse_one_cmd(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*result;

	cmd = create_cmd_util();
	if (!cmd)
		return (NULL);
	cmd->operator = TOKEN_END;
	if (*tokens && (*tokens)->type == TOKEN_LPAREN)
	{
		result = handle_subshell_cmd(tokens, cmd);
		if (!cmd->is_subshell || !cmd->subshell_tokens)
			return (free(cmd), NULL);
		*tokens = result;
		return (cmd);
	}
	if (!allocate_cmd_args(cmd, *tokens))
		return (free(cmd), NULL);
	result = fill_cmd_with_redirs(cmd, *tokens, shell);
	if (!result && shell->parse_error_type > 0)
		return (free(cmd->args), free(cmd), NULL);
	*tokens = result;
	return (cmd);
}
