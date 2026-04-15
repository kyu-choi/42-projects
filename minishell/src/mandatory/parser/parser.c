/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
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
 * @brief Parses one command from token stream
 * @param tokens Pointer to token stream (updated after parse)
 * @param shell Shell state for variable expansion
 * @return Newly allocated command structure
 * @details Allocates args array, processes redirections and arguments
 */
t_cmd	*parse_one_cmd(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	int		count;
	t_token	*result;

	cmd = create_cmd_util();
	if (!cmd)
		return (NULL);
	cmd->operator = TOKEN_END;
	count = count_word_tokens(*tokens);
	if (count < 2)
		count = 2;
	cmd->args = ft_calloc(count * 10 + 1, sizeof(char *));
	if (!cmd->args)
		return (free(cmd), NULL);
	result = fill_cmd_with_redirs(cmd, *tokens, shell);
	if (!result && shell->parse_error_type)
		return (free_cmds(cmd), NULL);
	*tokens = result;
	return (cmd);
}

/**
 * @brief Checks for syntax errors in pipeline
 * @param tokens Token list
 * @param shell Shell state
 * @return 1 if error, 0 otherwise
 */
static int	check_pipe_syntax(t_token *tokens, t_shell *shell)
{
	if (tokens->type == TOKEN_PIPE)
	{
		print_syntax_error("|");
		shell->parse_error_type = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Parses token list into command pipeline
 * @param tokens Token list from tokenizer
 * @param shell Shell state for variable expansion
 * @return Head of command pipeline linked list
 */
t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*new_cmd;

	if (!tokens)
		return (NULL);
	if (check_pipe_syntax(tokens, shell))
		return (NULL);
	head = parse_one_cmd(&tokens, shell);
	current = head;
	while (tokens && (tokens->type == TOKEN_PIPE
			|| tokens->type == TOKEN_AND || tokens->type == TOKEN_OR))
	{
		new_cmd = parse_next_cmd_util(&tokens, current, shell);
		if (!new_cmd)
			return (free_cmds(head), NULL);
		current->next = new_cmd;
		current = new_cmd;
	}
	return (head);
}

/**
 * @brief Frees redirection linked list
 * @param redirs Head of redirection list
 * @details Helper function for free_cmds
 */
static void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->heredoc_fd >= 0)
			close(tmp->heredoc_fd);
		free(tmp->file);
		free(tmp);
	}
}

/**
 * @brief Frees entire command pipeline
 * @param cmds Head of command linked list
 * @details Frees args array, redirections, and command nodes
 */
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_redirs(tmp->redirs);
		free(tmp);
	}
}
