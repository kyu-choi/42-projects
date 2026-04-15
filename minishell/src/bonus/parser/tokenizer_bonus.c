/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
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
 * @brief Creates new token with type and value
 * @param type Token type (WORD, PIPE, REDIR, etc.)
 * @param value String value (owned by token)
 * @return Newly allocated token, NULL on malloc failure
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;
	int		i;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->has_wildcard = check_wildcard(value);
	token->has_quoted = 0;
	if (value)
	{
		i = 0;
		while (value[i] && !token->has_quoted)
			if (value[i++] == '"' || value[i - 1] == '\'')
				token->has_quoted = 1;
	}
	token->next = NULL;
	return (token);
}

/**
 * @brief Extracts word token from current position
 * @param line Input line
 * @param i Pointer to current index (updated after word)
 * @param head Pointer to token list head
 */
static void	process_word(char *line, int *i, t_token **head)
{
	char	*word;
	int		len;

	word = extract_word_for_tokenizer(&line[*i]);
	len = 0;
	if (word)
		len = ft_strlen(word);
	if (word && len > 0)
	{
		add_token_to_list_util(head, create_token(TOKEN_WORD, word));
		*i += len;
	}
	else
	{
		if (word)
			free(word);
		if (line[*i])
			(*i)++;
	}
}

/**
 * @brief Processes tokens from line starting at index
 * @param line Input line
 * @param i Pointer to current index (updated)
 * @param head Pointer to token list head
 */
static void	process_tokens(char *line, int *i, t_token **head)
{
	if (check_fd_redir(line, i, head))
		return ;
	if (check_logical_operator(line, i, head))
		return ;
	if (check_redir_token(line, i, head))
		return ;
	if (check_redir_token2(line, i, head))
		return ;
	if (check_pipe_token(line, i, head))
		return ;
	if (check_semicolon_token(line, i, head))
		return ;
	process_word(line, i, head);
}

/**
 * @brief Tokenizes input line into token list
 * @param line Input string to tokenize
 * @return Head of token list, NULL if empty line
 * @details Handles whitespace, operators, quotes, and words
 */
t_token	*tokenize(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '#')
		return (NULL);
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			break ;
		process_tokens(line, &i, &head);
	}
	return (head);
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
