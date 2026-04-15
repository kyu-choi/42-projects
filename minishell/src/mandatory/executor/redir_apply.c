/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Opens all redirection files and stores fds
 * @param redirs Redirection list
 * @param fds Array to store file descriptors
 * @param types Array to store redirection types
 * @return 0 on success, -1 if any open fails
 */
int	open_all_redirs(t_redir *redirs, int *fds, t_token_type *types)
{
	t_redir	*current;
	int		i;
	int		fd;

	current = redirs;
	i = 0;
	while (current)
	{
		types[i] = current->type;
		if (current->type == TOKEN_REDIR_HEREDOC)
			fd = 0;
		else
			fd = open_redir_file(current);
		if (fd < 0)
		{
			close_all_fds(fds, i);
			return (-1);
		}
		fds[i] = fd;
		current = current->next;
		i++;
	}
	return (0);
}

/**
 * @brief Applies redirections using opened file descriptors
 * @param redirs Redirection list
 * @param fds Array of opened file descriptors
 * @param count Number of redirections
 * @param shell Shell state for variable expansion
 */
static int	apply_single_redir(t_redir *redir, int fd, t_shell *shell)
{
	int	target_fd;

	if (redir->type == TOKEN_REDIR_HEREDOC)
	{
		if (handle_heredoc(redir, shell) < 0)
			return (-1);
		if (redir->heredoc_fd < 0)
			return (-1);
		target_fd = redir->fd;
		dup2(redir->heredoc_fd, target_fd);
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
		return (0);
	}
	if (fd < 0)
		return (-1);
	target_fd = redir->fd;
	dup2(fd, target_fd);
	close(fd);
	return (0);
}

/**
 * @brief Applies all opened file descriptors to their target descriptors
 * @param redirs Redirection list
 * @param fds Array of opened file descriptors
 * @param count Number of redirections
 * @param shell Shell state
 * @return 0 on success, -1 on error
 */
static int	apply_redir_fds(t_redir *redirs, int *fds, int count,
				t_shell *shell)
{
	t_redir	*current;
	int		i;

	current = redirs;
	i = 0;
	while (i < count)
	{
		if (apply_single_redir(current, fds[i], shell) < 0)
			return (-1);
		current = current->next;
		i++;
	}
	return (0);
}

/**
 * @brief Applies all redirections for command
 * @param redirs Redirection linked list
 * @param shell Shell state for variable expansion
 * @return 0 on success, -1 on error
 * @details Opens all files first, then applies if all succeed
 */
int	apply_redirections(t_redir *redirs, t_shell *shell)
{
	int				*fds;
	t_token_type	*types;
	int				count;
	int				result;

	if (!redirs)
		return (0);
	count = count_redirs(redirs);
	fds = malloc(sizeof(int) * count);
	types = malloc(sizeof(t_token_type) * count);
	if (!fds || !types)
	{
		free(fds);
		free(types);
		return (-1);
	}
	result = open_all_redirs(redirs, fds, types);
	if (result == 0)
		result = apply_redir_fds(redirs, fds, count, shell);
	free(fds);
	free(types);
	return (result);
}
