/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"
#include <sys/wait.h>

/**
 * @brief Copies a range of tokens from start to end
 * @param start Starting token (inclusive)
 * @param end Ending token (exclusive)
 * @return New copied token list
 */
t_token	*copy_token_range(t_token *start, t_token *end);

/**
 * @brief Frees entire token linked list
 * @param tokens Token list to free
 */
void	free_token_list(t_token *tokens);

/**
 * @brief Finds matching closing parenthesis
 * @param start Starting left parenthesis token
 * @param depth_ptr Pointer to depth counter
 * @return Matching right parenthesis token
 */
t_token	*find_matching_paren(t_token *start, int *depth_ptr);

/**
 * @brief Executes subshell commands in child process
 * @param tokens Token list to parse and execute
 * @param shell Shell state with environment
 */
static void	execute_child_process(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd_list;
	int		status;

	cmd_list = parse(tokens, shell);
	if (!cmd_list)
	{
		if (shell->parse_error_type == 2)
			exit(2);
		exit(1);
	}
	status = execute_with_bonus(shell, cmd_list);
	exit(status);
}

/**
 * @brief Waits for child process and returns exit status
 * @param pid Process ID to wait for
 * @return Child process exit status
 */
static int	wait_child_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * @brief Executes commands in subshell (fork + recursive parse/execute)
 * @param tokens Tokens inside parenthesis
 * @param shell Shell state with environment
 * @return Subshell exit status
 */
static int	execute_in_subshell(t_token *tokens, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		execute_child_process(tokens, shell);
	return (wait_child_status(pid));
}

/**
 * @brief Executes parenthesized commands in subshell
 * 
 * @param start LPAREN token
 * @param end Pointer to set next token after RPAREN
 * @param shell Shell state with environment
 * @return int Subshell exit status
 */
int	execute_subshell(t_token *start, t_token **end, t_shell *shell)
{
	t_token	*group_end;
	t_token	*inner_tokens;
	int		result;
	int		depth;

	if (!start || start->type != TOKEN_LPAREN)
		return (1);
	group_end = find_matching_paren(start->next, &depth);
	if (depth != 0)
		return (1);
	inner_tokens = copy_token_range(start->next, group_end);
	if (!inner_tokens)
		return (1);
	result = execute_in_subshell(inner_tokens, shell);
	free_token_list(inner_tokens);
	*end = group_end->next;
	return (result);
}

/**
 * @brief Executes subshell command from parser
 * @param tokens Inner tokens (without parentheses)
 * @param shell Shell state
 * @return Subshell exit status
 */
int	execute_subshell_cmd(t_token *tokens, t_shell *shell)
{
	int		result;

	if (!tokens)
		return (0);
	result = execute_in_subshell(tokens, shell);
	return (result);
}
