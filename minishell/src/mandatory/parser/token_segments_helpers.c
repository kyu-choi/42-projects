/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_segments_helpers.c                           :+:      :+:    :+:   */
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
 * @brief Skips over a quoted section
 * @param str Input string
 * @param i Current index at opening quote
 * @return Index after closing quote (or end of string)
 */
int	skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

/**
 * @brief Checks if $ should be skipped (before quote)
 * @param str Input string
 * @param i Current index
 * @return 1 if $" or $' pattern found, 0 otherwise
 */
int	should_skip_dollar(char *str, int i)
{
	if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
		return (1);
	return (0);
}

/**
 * @brief Finds end of unquoted section
 * @param str Input string
 * @param i Starting index
 * @return Index where quote or $" pattern begins
 * @details Handles backslash escapes by skipping 2 characters
 */
int	find_unquoted_end(char *str, int i)
{
	while (str[i] && str[i] != '\'' && str[i] != '"')
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			continue ;
		}
		if (should_skip_dollar(str, i))
			break ;
		i++;
	}
	return (i);
}
