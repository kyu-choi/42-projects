/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_redir_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/05 00:00:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Expands argument if wildcard present
 * @param processed Processed value
 * @param has_wildcard Wildcard flag
 * @return Expanded array or NULL if no wildcard
 */
char	**expand_arg_if_needed(char *processed, int has_wildcard)
{
	char	**expanded;

	if (!has_wildcard)
		return (NULL);
	expanded = expand_pattern(processed);
	return (expanded);
}

/**
 * @brief Checks for ambiguous redirection
 * @param processed Processed filename
 * @param has_wildcard Wildcard flag
 * @param shell Shell state
 * @return 0 if valid, -1 if ambiguous
 */
int	check_ambiguous_redir(char *processed, int has_wildcard, t_shell *shell)
{
	char	**expanded;

	if (!has_wildcard)
		return (0);
	expanded = expand_pattern(processed);
	if (!expanded || !expanded[0])
		return (0);
	if (expanded[1])
	{
		write(2, "minishell: ", 11);
		write(2, processed, ft_strlen(processed));
		write(2, ": ambiguous redirect\n", 21);
		ft_free_split(expanded);
		shell->parse_error_type = 1;
		return (1);
	}
	ft_free_split(expanded);
	return (0);
}

/**
 * @brief Extracts redirection filename
 * @param processed Processed value
 * @param has_wildcard Wildcard flag
 * @return Filename string, NULL on error
 */
char	*get_redir_filename(char *processed, int has_wildcard)
{
	char	**expanded;
	char	*filename;

	if (!has_wildcard)
		return (processed);
	expanded = expand_pattern(processed);
	if (!expanded || !expanded[0])
		return (processed);
	if (expanded[1])
	{
		ft_free_split(expanded);
		free(processed);
		return (NULL);
	}
	filename = expanded[0];
	free(expanded);
	free(processed);
	return (filename);
}
