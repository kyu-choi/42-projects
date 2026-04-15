/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 01:25:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 12:25:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Processes single command line
 * @param shell Shell state
 * @param line Command line to process
 * @details Tokenizes, parses, and executes one command
 */
static void	process_single_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!line || *line == '\0')
		return ;
	shell->parse_error_type = 0;
	tokens = tokenize(line);
	if (!tokens)
		return ;
	cmds = parse(tokens, shell);
	free_tokens(tokens);
	if (!cmds)
	{
		shell->last_exit_status = shell->parse_error_type;
		return ;
	}
	shell->last_exit_status = execute(shell, cmds);
	free_cmds(cmds);
}

/**
 * @brief Handles one segment between semicolons
 * @param shell Shell state
 * @param line Full input line
 * @param start Start index of segment
 * @param end End index of segment
 */
static void	handle_segment_range(t_shell *shell, char *line,
				size_t start, size_t end)
{
	char	*segment;
	char	*trimmed;

	if (end <= start)
		return ;
	segment = ft_substr(line, start, end - start);
	if (!segment)
		return ;
	trimmed = ft_strtrim(segment, " \t");
	free(segment);
	if (!trimmed)
		return ;
	if (trimmed[0])
		process_single_line(shell, trimmed);
	free(trimmed);
}

/**
 * @brief Processes line split by semicolons
 * @param shell Shell state
 * @param line Input line with possible semicolons
 * @details Respects quotes when splitting
 */
static void	process_semicolon_segments(t_shell *shell, char *line)
{
	size_t	i;
	size_t	start;
	int		in_single;
	int		in_double;

	i = 0;
	start = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '"' && !in_single)
			in_double = !in_double;
		else if (line[i] == ';' && !in_single && !in_double)
		{
			handle_segment_range(shell, line, start, i);
			start = i + 1;
		}
		i++;
	}
	handle_segment_range(shell, line, start, i);
}

/**
 * @brief Main entry point for processing input line
 * @param shell Shell state
 * @param line Input line from readline
 * @details Adds to history and processes semicolon-separated commands
 */
void	process_line(t_shell *shell, char *line)
{
	if (!line || *line == '\0')
		return ;
	add_history(line);
	process_semicolon_segments(shell, line);
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
