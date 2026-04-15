/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_segments_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/07 00:00:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Creates new segment
 * @param value Segment value
 * @param quoted Quote type (0=none, 1=single, 2=double)
 * @return New segment or NULL on failure
 */
t_segment	*create_segment(char *value, int quoted)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->value = value;
	seg->quoted = quoted;
	seg->next = NULL;
	return (seg);
}

/**
 * @brief Adds segment to list
 * @param head Pointer to list head
 * @param seg Segment to add
 */
void	add_segment(t_segment **head, t_segment *seg)
{
	t_segment	*curr;

	if (!*head)
	{
		*head = seg;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = seg;
}

/**
 * @brief Frees segment list
 * @param segments Head of list
 */
void	free_segments(t_segment *segments)
{
	t_segment	*tmp;

	while (segments)
	{
		tmp = segments;
		segments = segments->next;
		free(tmp->value);
		free(tmp);
	}
}
