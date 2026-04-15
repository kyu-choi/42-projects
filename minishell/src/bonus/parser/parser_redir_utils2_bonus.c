/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Escapes wildcards in quoted segments by converting to special char
 * @param segments Segment list to process
 */
void	escape_wildcards_in_quoted_segs(t_segment *segments)
{
	t_segment	*seg;
	int			i;

	seg = segments;
	while (seg)
	{
		if (seg->quoted)
		{
			i = 0;
			while (seg->value[i])
			{
				if (seg->value[i] == '*')
					seg->value[i] = '\x01';
				i++;
			}
		}
		seg = seg->next;
	}
}

/**
 * @brief Adds expanded wildcard arguments to command args array
 * @param cmd Command structure
 * @param expanded Expanded argument array
 * @param i Current index in args array
 */
void	add_expanded_args(t_cmd *cmd, char **expanded, int *i)
{
	int	k;

	restore_wildcards_in_array(expanded);
	k = 0;
	while (expanded[k])
		cmd->args[(*i)++] = expanded[k++];
	free(expanded);
}

/**
 * @brief Processes a single field with optional wildcard expansion
 * @param cmd Command to add field to
 * @param field Field string to process
 * @param has_wc Whether field contains wildcards
 * @param i Current index in args array
 */
void	process_field(t_cmd *cmd, char *field, int has_wc, int *i)
{
	char	**expanded;

	if (has_wc)
	{
		expanded = expand_arg_if_needed(field, has_wc);
		if (expanded)
		{
			add_expanded_args(cmd, expanded, i);
			free(field);
		}
		else
		{
			restore_wildcards(field);
			cmd->args[(*i)++] = field;
		}
	}
	else
	{
		restore_wildcards(field);
		cmd->args[(*i)++] = field;
	}
}

/**
 * @brief Processes redirection word with expansion and ambiguity checking
 * @param tok Token containing the word
 * @param shell Shell state for expansion
 * @return Processed word string, or NULL on error/ambiguity
 */
char	*process_redir_word(t_token *tok, t_shell *shell)
{
	t_segment	*segments;
	char		**fields;
	int			count;
	char		*res;

	segments = split_into_segments(tok->value);
	if (!segments)
		return (NULL);
	escape_wildcards_in_quoted_segs(segments);
	fields = process_segments_to_fields(segments, shell, &count);
	free_segments(segments);
	if (!fields)
		return (NULL);
	if (count != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tok->value, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		shell->parse_error_type = 1;
		return (ft_free_split(fields), NULL);
	}
	res = fields[0];
	return (free(fields), res);
}

t_token	*process_word_token(t_cmd *cmd, t_token *tok, t_shell *shell, int *i)
{
	t_segment	*segments;
	char		**fields;
	int			count;
	int			j;

	segments = split_into_segments(tok->value);
	if (!segments)
		return (tok->next);
	escape_wildcards_in_quoted_segs(segments);
	fields = process_segments_to_fields(segments, shell, &count);
	free_segments(segments);
	if (!fields)
		return (tok->next);
	j = 0;
	while (j < count)
	{
		process_field(cmd, fields[j],
			tok->has_wildcard || check_wildcard(fields[j]), i);
		j++;
	}
	free(fields);
	return (tok->next);
}
