/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/21 02:54:10 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Opens file for redirection without applying
 * @param redir Redirection with type and filename
 * @return File descriptor on success, -1 on error
 */
int	open_redir_file(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == TOKEN_REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		return (0);
	if (fd < 0)
		perror(redir->file);
	return (fd);
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
