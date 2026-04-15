/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 12:05:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Safe malloc wrapper with error handling
 * @param size Number of bytes to allocate
 * @return Allocated memory pointer
 * @details Exits program with error if allocation fails
 */
void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_error("malloc failed");
		exit(1);
	}
	return (ptr);
}

/**
 * @brief Prints error message to stderr
 * @param msg Error message to print
 * @details Prefixes message with "minishell: "
 */
void	ft_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

/**
 * @brief Checks if character is a quote
 * @param c Character to check
 * @return 1 if single or double quote, 0 otherwise
 */
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/**
 * @brief Reads one line from pipe (stdin)
 * @return Line without newline, NULL on EOF
 * @details Used in non-interactive mode
 */
char	*read_line_from_pipe(void)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, "\n");
	free(line);
	return (trimmed);
}

/**
 * @brief Appends next line to current line
 * @param line Current line (freed)
 * @param next Next line (freed)
 * @return Joined line with newline between
 */
char	*append_line(char *line, char *next)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(line, "\n");
	joined = ft_strjoin(tmp, next);
	free(tmp);
	free(line);
	free(next);
	return (joined);
}
