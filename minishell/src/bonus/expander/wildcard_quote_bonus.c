/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_quote_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

#define WILDCARD_PLACEHOLDER '\x01'

/**
 * @brief Escapes wildcard characters in temporary string
 * @param temp Temporary string to modify in-place
 * @details Replaces '*' with placeholder character to prevent expansion
 */
static void	escape_wildcards_in_temp(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '*')
			temp[i] = WILDCARD_PLACEHOLDER;
		i++;
	}
}

static char	*append_segment(char *result, char *temp)
{
	char	*new_result;

	new_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (new_result);
}

char	*escape_quoted_wildcards(t_segment *segments)
{
	char		*result;
	char		*temp;
	t_segment	*seg;

	result = ft_strdup("");
	seg = segments;
	while (seg)
	{
		temp = ft_strdup(seg->value);
		if (seg->quoted)
			escape_wildcards_in_temp(temp);
		result = append_segment(result, temp);
		seg = seg->next;
	}
	return (result);
}

/**
 * @brief Restores escaped wildcards to literal asterisks
 * @param str String with escaped wildcards
 */
void	restore_wildcards(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == WILDCARD_PLACEHOLDER)
			str[i] = '*';
		i++;
	}
}

/**
 * @brief Restores wildcards in expanded file list
 * @param files Array of expanded filenames
 */
void	restore_wildcards_in_array(char **files)
{
	int	i;

	if (!files)
		return ;
	i = 0;
	while (files[i])
	{
		restore_wildcards(files[i]);
		i++;
	}
}
