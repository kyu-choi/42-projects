/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
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
	token->has_quoted = 0;
	if (value)
	{
		i = 0;
		while (value[i])
		{
			if (value[i] == '"' || value[i] == '\'')
				token->has_quoted = 1;
			i++;
		}
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

	word = extract_word_for_tokenizer(&line[*i]);
	if (word)
	{
		add_token_to_list_util(head, create_token(TOKEN_WORD, word));
		*i += ft_strlen(word);
	}
}

/**
 * @brief Checks for special tokens at line start
 * @param line Input string
 * @param i Pointer to current index
 * @return 1 if should return early, 0 to continue
 */
static int	check_line_start(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (line[*i] == '#')
		return (1);
	if (line[*i] == ';')
	{
		print_syntax_error(";");
		return (1);
	}
	return (0);
}

/**
 * @brief Processes tokens in the line
 * @param line Input string
 * @param i Pointer to current index
 * @param head Pointer to token list head
 */
static void	process_tokens(char *line, int *i, t_token **head)
{
	while (line[*i])
	{
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			(*i)++;
		if (!line[*i])
			break ;
		if (check_redir_token(line, i, head))
			continue ;
		if (check_redir_token2(line, i, head))
			continue ;
		if (check_pipe_token(line, i, head))
			continue ;
		process_word(line, i, head);
	}
}

/**
 * @brief Tokenizes input line into token list
 * @param line Input string to tokenize
 * @return Head of token list, NULL if empty line
 */
t_token	*tokenize(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	if (check_line_start(line, &i))
		return (NULL);
	process_tokens(line, &i, &head);
	return (head);
}
