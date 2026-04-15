/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 01:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 12:25:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Frees a semicolon token and advances the token list
 * @param semicolon Semicolon token to free
 * @param tokens Pointer to token list to update
 */
static void	free_semicolon_token(t_token *semicolon, t_token **tokens)
{
	*tokens = semicolon->next;
	free(semicolon->value);
	free(semicolon);
}

/**
 * @brief Splits token list at first semicolon, returning the head segment
 * @param tokens Pointer to token list to split
 * @return Head of the split token segment before semicolon
 */
static t_token	*split_at_semicolon(t_token **tokens)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;

	head = *tokens;
	if (!head)
		return (NULL);
	current = head;
	prev = NULL;
	while (current && current->type != TOKEN_SEMICOLON)
	{
		prev = current;
		current = current->next;
	}
	if (current && current->type == TOKEN_SEMICOLON)
	{
		if (prev)
			prev->next = NULL;
		else
			head = NULL;
		free_semicolon_token(current, tokens);
	}
	else
		*tokens = NULL;
	return (head);
}

/**
 * @brief Processes a group of tokens as a single command sequence
 * @param shell Shell state
 * @param tokens Token list to parse and execute
 */
static void	process_token_group(t_shell *shell, t_token *tokens)
{
	t_cmd	*cmds;

	if (!tokens)
		return ;
	cmds = parse(tokens, shell);
	if (!cmds)
	{
		shell->last_exit_status = shell->parse_error_type;
		return ;
	}
	shell->last_exit_status = execute_with_bonus(shell, cmds);
	free_cmds(cmds);
}

/**
 * @brief Processes a line of input by tokenizing and executing commands
 * @param shell Shell state
 * @param line Input line to process
 * @details Splits line at semicolons and executes each command group separately
 */
void	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_token	*group;

	if (!line || *line == '\0')
		return ;
	add_history(line);
	shell->parse_error_type = 0;
	tokens = tokenize_with_bonus(line);
	if (!tokens)
		return ;
	while (tokens)
	{
		group = split_at_semicolon(&tokens);
		if (group)
		{
			process_token_group(shell, group);
			free_tokens(group);
		}
	}
}

/**
 * @brief Reads input line based on interactive mode
 * @param shell Shell state
 * @return Input line, NULL on EOF
 */
char	*read_input(t_shell *shell)
{
	if (shell->is_interactive)
		return (readline(PROMPT));
	return (read_line_from_pipe());
}
