/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_utils_bonus.c                             :+:      :+:    :+:   */
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
 * @brief Frees token list memory
 * @param tokens Token list to free
 */
void	free_token_list(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

/**
 * @brief Finds matching closing parenthesis by tracking depth
 * @param start Token after LPAREN
 * @param depth_ptr Pointer to store final depth (0 if matched)
 * @return Token at RPAREN, or last token if unmatched
 */
t_token	*find_matching_paren(t_token *start, int *depth_ptr)
{
	t_token	*current;
	int		depth;

	depth = 1;
	current = start;
	while (current && depth > 0)
	{
		if (current->type == TOKEN_LPAREN)
			depth++;
		else if (current->type == TOKEN_RPAREN)
		{
			depth--;
			if (depth == 0)
				break ;
		}
		current = current->next;
	}
	*depth_ptr = depth;
	return (current);
}
