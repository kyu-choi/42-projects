/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:06:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
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
		&& str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != '&'
		&& str[i] != '(' && str[i] != ')' && str[i] != ';')
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
 * @brief Creates special single-character token
 * @param c Character to tokenize
 * @param head Pointer to token list head
 */
void	add_special_char_token(char c, t_token **head)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	add_token_to_list_util(head, create_token(TOKEN_WORD, ft_strdup(str)));
}
