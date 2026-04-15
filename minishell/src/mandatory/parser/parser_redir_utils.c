/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 11:29:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
 * @brief Counts WORD tokens before pipe or end
 * @param tokens Token list to count
 * @return Number of word tokens (excluding redirections)
 * @details Skips redirection operators and their filenames
 */
int	count_word_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		else if (is_redir_token(tokens->type))
		{
			tokens = tokens->next;
			if (!tokens)
				break ;
		}
		tokens = tokens->next;
	}
	return (count);
}

/**
 * @brief Validates redirection syntax
 * @param tok Token following redirection operator
 * @param shell Shell state for error reporting
 * @return 0 if valid, 1 on syntax error
 */
int	check_redir_syntax(t_token *tok, t_shell *shell)
{
	if (!tok || tok->type != TOKEN_WORD)
	{
		if (tok)
			print_syntax_error(tok->value);
		else
			print_syntax_error("newline");
		shell->parse_error_type = 2;
		return (1);
	}
	return (0);
}
