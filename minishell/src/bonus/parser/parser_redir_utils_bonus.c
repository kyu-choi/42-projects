/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils_bonus.c                         :+:      :+:    :+:   */
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
 * @brief Counts word tokens until operator or end
 * @param tokens Token list to count
 * @return Number of WORD tokens before operator
 */
int	count_word_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE
		&& tokens->type != TOKEN_AND && tokens->type != TOKEN_OR
		&& tokens->type != TOKEN_BACKGROUND)
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
 * @brief Creates redirection structure from token data
 * @param redir_type Type of redirection
 * @param processed Processed filename
 * @param redir_tok Original redirection token
 * @param expand Whether to expand heredoc variables
 * @return Newly created redirection structure
 */
t_redir	*create_redir_from_token(t_token_type redir_type, char *processed,
		t_token *redir_tok, int expand)
{
	t_redir	*new_redir;

	new_redir = create_redir(redir_type, processed, expand);
	if (redir_tok->value && ft_isdigit(redir_tok->value[0]))
		new_redir->fd = redir_tok->value[0] - '0';
	return (new_redir);
}
