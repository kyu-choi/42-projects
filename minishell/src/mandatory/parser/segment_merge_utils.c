/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_merge_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Merges two strings and frees both
 * @param s1 First string (freed)
 * @param s2 Second string (freed)
 * @return Newly allocated concatenated string
 * @details Handles NULL inputs gracefully
 */
char	*merge_str(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	free(s1);
	free(s2);
	return (result);
}

/**
 * @brief Adds field to results array
 * @param results Pointer to results array
 * @param count Pointer to field count
 * @param field Field to add (NULL fields are ignored)
 */
void	add_field(char ***results, int *count, char *field)
{
	if (field)
		(*results)[(*count)++] = field;
}

/**
 * @brief Handles empty expanded strings
 * @param str Expanded string to check
 * @param seg Original segment
 * @param current Pointer to current accumulated field
 * @return 1 if handled (empty), 0 otherwise
 * @details Quoted empty strings become empty fields
 */
int	handle_empty_str(char *str, t_segment *seg, char **current)
{
	if (!str || !*str)
	{
		if (str)
			free(str);
		if (seg->quoted)
			*current = merge_str(*current, ft_strdup(""));
		return (1);
	}
	return (0);
}

/**
 * @brief Processes split words array
 * @param words Array of words from split
 * @param lead Has leading IFS whitespace flag
 * @param ctx Merge context
 * @return Number of words processed
 * @details First word merges if no leading IFS, others become separate fields
 */
int	process_words_loop(char **words, int lead, t_merge_ctx *ctx)
{
	int	i;

	i = -1;
	while (words[++i])
	{
		if (i == 0 && !lead)
			*(ctx->current) = merge_str(*(ctx->current), words[i]);
		else
		{
			add_field(ctx->results, ctx->count, *(ctx->current));
			*(ctx->current) = words[i];
		}
	}
	return (i);
}
