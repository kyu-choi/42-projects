/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Opens an input file for redirection
 * @param redir Redirection structure with filename
 * @param shell Shell state for error reporting
 * @return File descriptor on success, -1 on error
 */
static int	open_input_file(t_redir *redir, t_shell *shell)
{
	int		fd;
	char	*filename;

	if (check_ambiguous_redir(redir->file,
			ft_strchr(redir->file, '*') != NULL, shell))
		return (-1);
	filename = get_redir_filename(ft_strdup(redir->file),
			ft_strchr(redir->file, '*') != NULL);
	if (!filename)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (filename != redir->file && filename)
		free(filename);
	if (fd < 0)
		perror(redir->file);
	return (fd);
}

/**
 * @brief Opens an output file for redirection with specified flags
 * @param redir Redirection structure with filename
 * @param shell Shell state for error reporting
 * @param flags Open flags (O_TRUNC for >, O_APPEND for >>)
 * @return File descriptor on success, -1 on error
 */
static int	open_output_file(t_redir *redir, t_shell *shell, int flags)
{
	int		fd;
	char	*filename;

	if (check_ambiguous_redir(redir->file,
			ft_strchr(redir->file, '*') != NULL, shell))
		return (-1);
	filename = get_redir_filename(ft_strdup(redir->file),
			ft_strchr(redir->file, '*') != NULL);
	if (!filename)
		return (-1);
	fd = open(filename, flags, 0644);
	if (filename != redir->file && filename)
		free(filename);
	if (fd < 0)
		perror(redir->file);
	return (fd);
}

/**
 * @brief Opens file for redirection without applying
 * @param redir Redirection with type and filename
 * @return File descriptor on success, -1 on error
 */
int	open_redir_file(t_redir *redir, t_shell *shell)
{
	if (redir->type == TOKEN_REDIR_IN)
		return (open_input_file(redir, shell));
	else if (redir->type == TOKEN_REDIR_APPEND)
		return (open_output_file(redir, shell,
				O_WRONLY | O_CREAT | O_APPEND));
	else if (redir->type == TOKEN_REDIR_OUT)
		return (open_output_file(redir, shell,
				O_WRONLY | O_CREAT | O_TRUNC));
	return (0);
}

/**
 * @brief Closes all opened file descriptors
 * @param fds Array of file descriptors
 * @param count Number of descriptors
 */
void	close_all_fds(int *fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (fds[i] >= 0)
			close(fds[i]);
		i++;
	}
}

/**
 * @brief Counts redirections in list
 * @param redirs Redirection linked list
 * @return Number of redirections
 */
int	count_redirs(t_redir *redirs)
{
	int		count;
	t_redir	*current;

	count = 0;
	current = redirs;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
