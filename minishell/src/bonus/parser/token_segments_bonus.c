/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_segments_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Creates a new segment with value and quoted flag
 * @param value Segment string value
 * @param quoted Whether segment was quoted (0=no, 1=yes)
 * @return New segment structure, or NULL on failure
 */
t_segment	*create_segment(char *value, int quoted);

/**
 * @brief Adds segment to end of segment list
 * @param head Pointer to segment list head
 * @param seg Segment to add
 */
void		add_segment(t_segment **head, t_segment *seg);

/**
 * @brief Frees all segments in list
 * @param segments Segment list to free
 */
void		free_segments(t_segment *segments);

/**
 * @brief Skips over a quoted section in string
 * @param str Input string
 * @param i Starting index at quote character
 * @return Index after closing quote
 */
int			skip_quote(char *str, int i);

/**
 * @brief Checks if dollar sign should be skipped (not expanded)
 * @param str Input string
 * @param i Index of dollar sign
 * @return 1 if should skip, 0 otherwise
 */
int			should_skip_dollar(char *str, int i);

/**
 * @brief Finds end of unquoted segment
 * @param str Input string
 * @param i Starting index
 * @return Index at end of unquoted section
 */
int			find_unquoted_end(char *str, int i);

/**
 * @brief Processes quoted section and creates segment
 * @param value Token value string
 * @param i Current index at opening quote
 * @param head Pointer to segment list head
 * @return Index after closing quote
 * @details Creates segment with quote_type (1=single, 2=double)
 */
static int	process_quoted(char *value, int i, t_segment **head)
{
	int		start;
	int		quote_type;
	char	*sub;

	quote_type = (value[i] == '\'') + 1;
	start = i;
	i = skip_quote(value, i);
	sub = ft_substr(value, start, i - start);
	add_segment(head, create_segment(sub, quote_type));
	return (i);
}

/**
 * @brief Processes unquoted section and creates segment
 * @param value Token value string
 * @param i Current index
 * @param head Pointer to segment list head
 * @return Index after unquoted section
 * @details Handles escaped $ before quotes correctly
 */
static int	process_unquoted(char *value, int i, t_segment **head)
{
	int		start;
	char	*sub;

	start = i;
	i = find_unquoted_end(value, i);
	if (i > start)
	{
		if (should_skip_dollar(value, i - 1))
		{
			if (i < 2 || value[i - 2] != '\\')
				i--;
		}
		sub = ft_substr(value, start, i - start);
		add_segment(head, create_segment(sub, 0));
	}
	if (should_skip_dollar(value, i))
		i++;
	return (i);
}

/**
 * @brief Splits token value into quoted/unquoted segments
 * @param value Token value to split
 * @return Head of segment linked list
 * @details Segments are processed before variable expansion
 */
t_segment	*split_into_segments(char *value)
{
	t_segment	*head;
	int			i;

	head = NULL;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			i = process_quoted(value, i, &head);
		else
			i = process_unquoted(value, i, &head);
	}
	return (head);
}
