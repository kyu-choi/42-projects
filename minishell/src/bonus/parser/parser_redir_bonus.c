/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 11:29:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

t_redir	*create_redir_from_token(t_token_type type, char *val, t_token *tok,
			int expand);
char	*process_redir_word(t_token *tok, t_shell *shell);
t_token	*process_word_token(t_cmd *cmd, t_token *tok, t_shell *shell, int *i);

/**
 * @brief Checks if token type is a redirection operator
 * @param type Token type to check
 * @return 1 if redirection token, 0 otherwise
 */
int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

/**
 * @brief Gets the processed value for a redirection target
 * @param type Redirection type
 * @param tok Token containing the filename
 * @param shell Shell state for variable expansion
 * @return Processed redirection target string, or NULL on error
 */
static char	*get_redir_val(t_token_type type, t_token *tok, t_shell *shell)
{
	char	*val;

	if (type == TOKEN_REDIR_HEREDOC)
		return (remove_quotes(tok->value));
	val = process_redir_word(tok, shell);
	if (!val)
		return (NULL);
	if (check_ambiguous_redir(val, check_wildcard(val), shell))
	{
		free(val);
		return (NULL);
	}
	restore_wildcards(val);
	return (val);
}

/**
 * @brief Parses and processes a redirection operator and its target
 * @param tok Current token (redirection operator)
 * @param cmd Command to add redirection to
 * @param shell Shell state
 * @return Next token to process, or NULL on error
 */
t_token	*handle_redir_in_parse(t_token *tok, t_cmd *cmd, t_shell *shell)
{
	t_token_type	type;
	char			*val;
	t_redir			*new;
	t_token			*rtok;

	rtok = tok;
	type = tok->type;
	tok = tok->next;
	if (!tok || tok->type != TOKEN_WORD)
	{
		if (tok)
			print_syntax_error_bonus(tok->value);
		else
			print_syntax_error_bonus(NULL);
		shell->parse_error_type = 2;
		return (NULL);
	}
	val = get_redir_val(type, tok, shell);
	if (!val)
		return (NULL);
	new = create_redir_from_token(type, val, rtok,
			type == TOKEN_REDIR_HEREDOC && !tok->has_quoted);
	add_redir(&cmd->redirs, new);
	free(val);
	return (tok->next);
}

t_token	*fill_cmd_with_redirs(t_cmd *cmd, t_token *tok, t_shell *shell)
{
	int	i;

	i = 0;
	while (tok && tok->type != TOKEN_PIPE
		&& tok->type != TOKEN_AND && tok->type != TOKEN_OR
		&& tok->type != TOKEN_BACKGROUND)
	{
		if (is_redir_token(tok->type))
		{
			tok = handle_redir_in_parse(tok, cmd, shell);
			if (!tok)
				return (NULL);
		}
		else
			tok = process_word_token(cmd, tok, shell, &i);
	}
	cmd->args[i] = NULL;
	return (tok);
}
