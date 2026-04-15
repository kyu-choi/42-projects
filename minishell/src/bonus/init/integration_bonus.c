/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:06:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Processes word token during tokenization
 *
 * @param line Input string
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
		if (line[*i] && line[*i] == ';')
			add_special_char_token(line[*i], head);
		if (line[*i])
			(*i)++;
	}
}

/**
 * @brief Processes one token type check during tokenization
 * 
 * @param line Input string
 * @param i Pointer to current index
 * @param head Pointer to token list head
 * @return 1 if token processed, 0 to continue
 */
static int	process_token_check(char *line, int *i, t_token **head)
{
	if (check_logical_operator(line, i, head))
		return (1);
	if (check_redir_token(line, i, head))
		return (1);
	if (check_redir_token2(line, i, head))
		return (1);
	if (check_pipe_token(line, i, head))
		return (1);
	if (check_semicolon_token(line, i, head))
		return (1);
	if (check_parenthesis_token(line, i, head))
		return (1);
	return (0);
}

/**
 * @brief Enhanced tokenizer with bonus operators support
 * 
 * This is a wrapper around the standard tokenizer that adds support
 * for logical operators (&&, ||) by calling check_logical_operator
 * before standard token checks.
 * 
 * @param line Input command line
 * @return Token list with bonus operators included
 */
t_token	*tokenize_with_bonus(char *line)
{
	t_token	*head;
	int		i;

	if (!line)
		return (NULL);
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
		if (process_token_check(line, &i, &head))
			continue ;
		process_word(line, &i, &head);
	}
	return (head);
}

/**
 * @brief Checks if command list has logical operators
 * 
 * Scans command list for TOKEN_AND or TOKEN_OR operators.
 * 
 * @param cmds Command linked list
 * @return 1 if && or || found, 0 otherwise
 */
static int	has_logical_operators(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->operator == TOKEN_AND || current->operator == TOKEN_OR)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Enhanced executor with bonus features support
 *
 * This wrapper adds support for:
 * - Logical operators (&&, ||) with short-circuit evaluation
 * - Parenthesis grouping for priority control
 * - Falls back to standard execution for non-bonus commands
 *
 * @param shell Shell state with environment
 * @param cmds Command pipeline to execute
 * @return Exit status of last command
 */
int	execute_with_bonus(t_shell *shell, t_cmd *cmds)
{
	if (!cmds)
		return (0);
	if (has_logical_operators(cmds))
		return (execute_with_operators(shell, cmds));
	return (execute(shell, cmds));
}
