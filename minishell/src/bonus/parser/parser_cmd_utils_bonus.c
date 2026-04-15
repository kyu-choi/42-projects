/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/07 00:00:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Creates a deep copy of a single token
 * @param src Source token to copy
 * @return Newly allocated token copy
 */
static t_token	*create_token_copy(t_token *src)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = src->type;
	new_token->value = ft_strdup(src->value);
	new_token->has_wildcard = src->has_wildcard;
	new_token->has_quoted = src->has_quoted;
	new_token->next = NULL;
	return (new_token);
}

/**
 * @brief Copies a range of tokens from linked list
 * @param start First token to copy
 * @param end Token after last token to copy (exclusive)
 * @return Head of newly allocated token list
 */
t_token	*copy_token_range(t_token *start, t_token *end)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	t_token	*prev;

	if (start == end)
		return (NULL);
	head = NULL;
	prev = NULL;
	current = start;
	while (current && current != end)
	{
		new_token = create_token_copy(current);
		if (!new_token)
			return (NULL);
		if (!head)
			head = new_token;
		if (prev)
			prev->next = new_token;
		prev = new_token;
		current = current->next;
	}
	return (head);
}

/**
 * @brief Extracts tokens within parentheses for subshell
 * @param tokens Pointer to token stream starting at LPAREN
 * @param cmd Command structure to fill with subshell data
 * @return Token after matching RPAREN, NULL on error
 */
static t_token	*extract_subshell_tokens(t_token **tokens, t_cmd *cmd)
{
	t_token	*current;
	t_token	*start;
	int		depth;

	if (!*tokens || (*tokens)->type != TOKEN_LPAREN)
		return (NULL);
	start = (*tokens)->next;
	depth = 1;
	current = start;
	while (current && depth > 0)
	{
		if (current->type == TOKEN_LPAREN)
			depth++;
		else if (current->type == TOKEN_RPAREN)
			depth--;
		if (depth > 0)
			current = current->next;
	}
	if (depth != 0)
		return (NULL);
	cmd->is_subshell = 1;
	cmd->subshell_tokens = copy_token_range(start, current);
	if (!cmd->subshell_tokens)
		return (NULL);
	return (current->next);
}

/**
 * @brief Handles subshell command parsing
 * @param tokens Pointer to token stream
 * @param cmd Command structure to fill
 * @return Next token after subshell, NULL on error
 */
t_token	*handle_subshell_cmd(t_token **tokens, t_cmd *cmd)
{
	t_token	*result;

	result = extract_subshell_tokens(tokens, cmd);
	if (!cmd->subshell_tokens)
		return (NULL);
	cmd->args = ft_calloc(1, sizeof(char *));
	return (result);
}

/**
 * @brief Allocates args array for command
 * @param cmd Command structure
 * @param tokens Token list to count words from
 * @return 1 on success, 0 on allocation failure
 */
int	allocate_cmd_args(t_cmd *cmd, t_token *tokens)
{
	int	count;

	count = count_word_tokens(tokens);
	if (count == 0)
		count = 1;
	cmd->args = ft_calloc(count * 100 + 1, sizeof(char *));
	if (!cmd->args)
		return (0);
	return (1);
}
