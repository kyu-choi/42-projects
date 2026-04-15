/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Writes expanded or literal line to heredoc
 * @param fd File descriptor to write to
 * @param line Input line to write
 * @param expand Whether to expand variables
 * @param shell Shell state for variable expansion
 */
static void	write_heredoc_content(int fd, char *line,
			int expand, t_shell *shell)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_heredoc_variables_bonus(line, shell);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

/**
 * @brief Checks if line matches heredoc delimiter
 * @param line Input line to check
 * @param delimiter Heredoc terminator string
 * @return 1 to continue, 0 if delimiter found
 */
static int	check_delimiter(char *line, char *delimiter)
{
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		return (0);
	return (1);
}

/**
 * @brief Reads heredoc input lines until delimiter
 * @param fd File descriptor to write to
 * @param delimiter Heredoc terminator string
 * @return 0 (always)
 * @details Prompts with >, stops at delimiter or EOF
 */
static char	*read_line_from_fd(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, "\n");
	free(line);
	return (trimmed);
}

/**
 * @brief Reads heredoc input lines until delimiter is found
 * @param fd File descriptor to write heredoc content to
 * @param delimiter Heredoc delimiter string
 * @param expand Whether to expand variables in heredoc
 * @param shell Shell state for variable expansion
 * @return 0 on success
 */
static int	read_heredoc_lines(int fd, char *delimiter,
			int expand, t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = read_line_from_fd(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			break ;
		}
		if (!check_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_heredoc_content(fd, line, expand, shell);
		free(line);
	}
	return (0);
}

/**
 * @brief Handles heredoc redirection (<<)
 * @param redir Redirection with delimiter
 * @param shell Shell state for variable expansion
 * @return 0 on success, -1 on error
 * @details Creates pipe, reads input, redirects to stdin
 */
int	handle_heredoc(t_redir *redir, t_shell *shell)
{
	int		pipe_fd[2];

	if (redir->heredoc_fd >= 0)
		return (0);
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	read_heredoc_lines(pipe_fd[1], redir->file,
		redir->expand_heredoc, shell);
	close(pipe_fd[1]);
	redir->heredoc_fd = pipe_fd[0];
	return (0);
}
