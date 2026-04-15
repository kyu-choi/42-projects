/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_full_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 22:06:36 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Checks for empty parentheses ()
 * @param tok Current token
 * @param shell Shell state for error handling
 * @return 1 if empty parentheses found, 0 otherwise
 */
int	check_empty_paren(t_token *tok, t_shell *shell)
{
	if (tok->type == TOKEN_LPAREN && tok->next
		&& tok->next->type == TOKEN_RPAREN)
	{
		write(2, "minishell: syntax error near unexpected token\n", 47);
		shell->parse_error_type = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Checks if token type is an operator
 * @param type Token type to check
 * @return 1 if operator (PIPE, AND, OR, BACKGROUND), 0 otherwise
 */
int	is_operator_token(t_token_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_BACKGROUND)
		return (1);
	return (0);
}

/**
 * @brief Finds matching closing parenthesis
 * @param tok Token after opening parenthesis
 * @return Token at closing parenthesis, NULL if unmatched
 */
t_token	*find_matching_rparen(t_token *tok)
{
	int	depth;

	depth = 1;
	tok = tok->next;
	while (tok && depth > 0)
	{
		if (tok->type == TOKEN_LPAREN)
			depth++;
		else if (tok->type == TOKEN_RPAREN)
			depth--;
		if (depth > 0)
			tok = tok->next;
	}
	return (tok);
}

/**
 * @brief Frees all redirections in a command
 * @param redirs Head of redirection linked list
 */
void	free_cmd_redirs(t_redir *redirs)
{
	t_redir	*tmp_redir;

	while (redirs)
	{
		tmp_redir = redirs;
		redirs = redirs->next;
		if (tmp_redir->heredoc_fd >= 0)
			close(tmp_redir->heredoc_fd);
		free(tmp_redir->file);
		free(tmp_redir);
	}
}
