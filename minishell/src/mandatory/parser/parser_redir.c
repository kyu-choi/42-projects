/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks redirection syntax for errors
 * @param tok Token to check
 * @param shell Shell state for error reporting
 * @return 0 if valid, non-zero on error
 */
int	check_redir_syntax(t_token *tok, t_shell *shell);

/**
 * @brief Creates a redirection structure from token information
 * @param redir_tok Redirection operator token
 * @param type Type of redirection
 * @param processed Processed filename/target
 * @param expand Whether to expand variables in heredoc
 * @return New redirection structure, or NULL on failure
 */
static t_redir	*create_redir_from_token(t_token *redir_tok,
				t_token_type type, char *processed, int expand)
{
	t_redir	*new_redir;

	new_redir = create_redir(type, processed, expand);
	if (!new_redir)
		return (NULL);
	if (redir_tok && redir_tok->value && ft_isdigit(redir_tok->value[0]))
		new_redir->fd = ft_atoi(redir_tok->value);
	return (new_redir);
}

/**
 * @brief Processes redirection target content with quote removal and expansion
 * @param tok Token containing the target
 * @param type Redirection type
 * @param shell Shell state for expansion
 * @param processed Output processed string
 * @return Whether heredoc should expand variables
 */
static int	process_redir_content(t_token *tok, t_token_type type,
				t_shell *shell, char **processed)
{
	if (type == TOKEN_REDIR_HEREDOC)
		*processed = remove_quotes(tok->value);
	else
		*processed = process_token_value_util(tok->value, shell);
	return (type == TOKEN_REDIR_HEREDOC && !tok->has_quoted);
}

t_token	*handle_redir_in_parse(t_token *tok, t_cmd *cmd, t_shell *shell)
{
	t_token_type	type;
	char			*processed;
	t_token			*redir_tok;
	t_redir			*new_redir;
	int				expand;

	redir_tok = tok;
	type = tok->type;
	tok = tok->next;
	if (check_redir_syntax(tok, shell))
		return (NULL);
	expand = process_redir_content(tok, type, shell, &processed);
	new_redir = create_redir_from_token(redir_tok, type, processed, expand);
	if (!new_redir)
	{
		free(processed);
		shell->parse_error_type = 1;
		return (NULL);
	}
	add_redir(&cmd->redirs, new_redir);
	free(processed);
	return (tok->next);
}

static t_token	*process_word_arg(t_cmd *cmd, t_token *tok,
					t_shell *shell, int *i)
{
	t_segment	*segments;
	char		**fields;
	int			field_count;
	int			j;

	segments = split_into_segments(tok->value);
	if (!segments)
		return (tok->next);
	fields = process_segments_to_fields(segments, shell, &field_count);
	free_segments(segments);
	if (!fields)
		return (tok->next);
	j = 0;
	while (j < field_count)
		cmd->args[(*i)++] = fields[j++];
	free(fields);
	return (tok->next);
}

t_token	*fill_cmd_with_redirs(t_cmd *cmd, t_token *tok, t_shell *shell)
{
	int	i;

	i = 0;
	while (tok && tok->type != TOKEN_PIPE)
	{
		if (is_redir_token(tok->type))
		{
			tok = handle_redir_in_parse(tok, cmd, shell);
			if (!tok)
				return (NULL);
		}
		else
			tok = process_word_arg(cmd, tok, shell, &i);
	}
	cmd->args[i] = NULL;
	return (tok);
}
