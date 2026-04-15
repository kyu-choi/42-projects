/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 09:27:33 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Skips over quoted section in tokenizer
 * @param str Input string
 * @param i Current index at opening quote
 * @return Index after closing quote (or end of string)
 * @details Handles both single and double quotes
 */
int	skip_quotes_in_tokenizer(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
	{
		if (quote == '"' && str[i] == '\\' && str[i + 1])
			i += 2;
		else
			i++;
	}
	if (str[i] == quote)
		i++;
	return (i);
}

/**
 * @brief Calculates length of word token
 * @param str Input string at word start
 * @return Length of word (stops at space, operator, or quote boundary)
 * @details Respects quoted sections and backslashes when calculating length
 */
int	get_word_len_for_tokenizer(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_quotes_in_tokenizer(str, i);
		else if (str[i] == '\\' && str[i + 1])
			i += 2;
		else
			i++;
	}
	return (i);
}

/**
 * @brief Extracts word from string for tokenizer
 * @param str Input string at word start
 * @return Newly allocated substring containing word
 * @details Uses get_word_len_for_tokenizer to determine length
 */
char	*extract_word_for_tokenizer(char *str)
{
	int		len;
	char	*word;

	len = get_word_len_for_tokenizer(str);
	word = ft_substr(str, 0, len);
	return (word);
}

/**
 * @brief Adds token to end of token list
 * @param head Pointer to token list head
 * @param new_token Token to append
 * @details Creates head if empty, otherwise appends to end
 */
void	add_token_to_list_util(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

/**
 * @brief Frees entire token linked list
 * @param tokens Head of token list to free
 */
void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
