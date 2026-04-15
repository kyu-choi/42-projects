/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 01:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 12:25:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Handles unclosed quotes by reading continuation
 * @param shell Shell state
 * @param line Current line with unclosed quote
 * @return Complete line or NULL on EOF
 */
static char	*handle_unclosed_quotes(t_shell *shell, char *line)
{
	char	*next_line;

	while (get_unclosed_quote(line))
	{
		if (shell->is_interactive)
			next_line = readline("> ");
		else
			next_line = read_line_from_pipe();
		if (!next_line)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for ", 2);
			ft_putstr_fd("matching quote\n", 2);
			break ;
		}
		line = append_line(line, next_line);
	}
	return (line);
}

static char	*read_next_part(t_shell *shell, char *line)
{
	char	*next_line;

	if (shell->is_interactive)
		next_line = readline("> ");
	else
		next_line = read_line_from_pipe();
	if (!next_line)
	{
		ft_putstr_fd("minishell: syntax error: unexpected EOF\n", 2);
		shell->parse_error_type = 2;
		free(line);
		return (NULL);
	}
	return (next_line);
}

static int	check_continuation(char *line)
{
	t_token	*tokens;

	tokens = tokenize(line);
	if (!tokens || !has_trailing_operator(tokens))
	{
		if (tokens)
			free_tokens(tokens);
		return (0);
	}
	free_tokens(tokens);
	return (1);
}

/**
 * @brief Handles commands ending with operators by reading continuation
 * @param shell Shell state
 * @param line Current line ending with operator
 * @return Complete command line or NULL on EOF/error
 * @details Prompts with "> " for additional input until command is complete
 */
static char	*handle_trailing_operator(t_shell *shell, char *line)
{
	char	*next_line;
	char	*joined;
	char	*temp;

	while (check_continuation(line))
	{
		next_line = read_next_part(shell, line);
		if (!next_line)
			return (NULL);
		temp = ft_strjoin(line, " ");
		free(line);
		joined = ft_strjoin(temp, next_line);
		free(temp);
		free(next_line);
		line = joined;
	}
	return (line);
}

/**
 * @brief Main shell read-eval loop
 * @param shell Shell state
 * @details Reads input, handles quotes, processes commands until EOF or error
 */
void	run_shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = read_input(shell);
		if (!line)
		{
			if (shell->is_interactive)
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		line = handle_unclosed_quotes(shell, line);
		if (!line)
			continue ;
		line = handle_trailing_operator(shell, line);
		if (!line)
			continue ;
		process_line(shell, line);
		free(line);
		if (!shell->is_interactive && shell->parse_error_type != 0)
			break ;
	}
	if (shell->parse_error_type != 0)
		shell->last_exit_status = shell->parse_error_type;
}
