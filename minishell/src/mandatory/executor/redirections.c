/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/03 14:03:52 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Creates new redirection node
 * @param type Redirection type (<, >, <<, >>)
 * @param file Target filename (copied)
 * @return Newly allocated redirection node
 */
t_redir	*create_redir(t_token_type type, char *file, int expand)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_HEREDOC)
		redir->fd = STDIN_FILENO;
	else
		redir->fd = STDOUT_FILENO;
	redir->expand_heredoc = expand;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

/**
 * @brief Adds redirection to end of list
 * @param head Pointer to redirection list head
 * @param new_redir Redirection to append
 */
void	add_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/**
 * @brief Handles input redirection (<)
 * @param redir Redirection with filename
 * @return 0 on success, -1 on error
 * @details Opens file read-only, redirects to stdin
 */
int	handle_input_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/**
 * @brief Handles output redirection (> or >>)
 * @param redir Redirection with filename and type
 * @return 0 on success, -1 on error
 * @details Creates/truncates (>) or appends (>>), redirects to stdout
 */
int	handle_output_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->file);
		return (-1);
	}
	dup2(fd, redir->fd);
	close(fd);
	return (0);
}
