/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_merge_bonus.c                              :+:      :+:    :+:   */
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
 * @brief Merges two strings into a newly allocated string
 * @param s1 First string
 * @param s2 Second string
 * @return New merged string, or NULL on failure
 */
char	*merge_str(char *s1, char *s2);

/**
 * @brief Adds a field to results array
 * @param results Pointer to results array
 * @param count Pointer to field count
 * @param field Field string to add
 */
void	add_field(char ***results, int *count, char *field);

/**
 * @brief Handles empty string edge cases during merge
 * @param str String to check
 * @param seg Current segment
 * @param current Current accumulated field
 * @return 1 if handled, 0 otherwise
 */
int		handle_empty_str(char *str, t_segment *seg, char **current);

/**
 * @brief Processes word-split array in merge context
 * @param words Word array from splitting
 * @param lead Whether segment has leading IFS
 * @param ctx Merge context
 * @return 0 on success, -1 on error
 */
int		process_words_loop(char **words, int lead, t_merge_ctx *ctx);

/**
 * @brief Flushes current accumulated field to results
 * @param ctx Merge context with current field pointer
 * @details Adds non-empty current field to results and resets to NULL
 */
static void	flush_current(t_merge_ctx *ctx)
{
	if (*(ctx->current))
	{
		add_field(ctx->results, ctx->count, *(ctx->current));
		*(ctx->current) = NULL;
	}
}

/**
 * @brief Handles word splitting for unquoted expanded segment
 * @param str Expanded string to split
 * @param ctx Merge context
 * @return 1 if string should be freed, 0 otherwise
 * @details Splits on IFS characters and handles leading/trailing whitespace
 */
static int	handle_word_split(char *str, t_merge_ctx *ctx)
{
	char	**words;
	int		lead;
	int		trail;
	int		i;

	lead = has_leading_ifs(str);
	trail = has_trailing_ifs(str);
	words = split_words(str);
	if (!words)
	{
		if (lead)
		{
			flush_current(ctx);
			return (1);
		}
		*(ctx->current) = merge_str(*(ctx->current), str);
		return (0);
	}
	if (lead)
		flush_current(ctx);
	i = process_words_loop(words, lead, ctx);
	if (trail && i > 0)
		flush_current(ctx);
	free(words);
	return (1);
}

/**
 * @brief Main processing loop for segments
 * @param seg Segment list to process
 * @param shell Shell state for variable expansion
 * @param ctx Merge context
 * @details Expands variables, handles quotes, and merges/splits fields
 */
static void	process_loop(t_segment *seg, t_shell *shell, t_merge_ctx *ctx)
{
	char	*str;
	int		should_free;

	while (seg)
	{
		str = process_token_value_util(seg->value, shell);
		if (handle_empty_str(str, seg, ctx->current))
			;
		else if (seg->quoted)
			*(ctx->current) = merge_str(*(ctx->current), str);
		else
		{
			should_free = handle_word_split(str, ctx);
			if (should_free)
				free(str);
		}
		seg = seg->next;
	}
}

/**
 * @brief Processes segments into field array
 * @param segments Segment linked list
 * @param shell Shell state for variable expansion
 * @param result_count Pointer to store number of fields
 * @return Array of field strings (NULL-terminated)
 * @details Main entry point for segment processing and field splitting
 */
char	**process_segments_to_fields(t_segment *segments,
			t_shell *shell, int *result_count)
{
	char		**results;
	char		*current;
	t_merge_ctx	ctx;

	results = malloc(sizeof(char *) * 1000);
	if (!results)
		return (NULL);
	*result_count = 0;
	current = NULL;
	ctx.results = &results;
	ctx.count = result_count;
	ctx.current = &current;
	process_loop(segments, shell, &ctx);
	add_field(&results, result_count, current);
	results[*result_count] = NULL;
	return (results);
}
