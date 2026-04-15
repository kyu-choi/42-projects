/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Handles backslash in heredoc expansion
 * @param str Input string
 * @param i Pointer to current index (at \)
 * @param res Current result string
 * @return Updated result string
 * @details Only $, \, and ` are escaped in heredoc
 */
static char	*handle_heredoc_backslash(char *str, int *i, char *res)
{
	if (str[*i + 1] == '$' || str[*i + 1] == '\\' || str[*i + 1] == '`')
	{
		(*i)++;
		return (append_char_to_str(res, str[(*i)++]));
	}
	return (append_char_to_str(res, str[(*i)++]));
}

/**
 * @brief Expands variables in heredoc content
 * @param str Heredoc line to expand
 * @param shell Shell state for variable values
 * @return Expanded string (newly allocated)
 * @details Expands $VAR but not quotes (heredoc has no quote processing)
 */
char	*expand_heredoc_variables(char *str, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			result = handle_heredoc_backslash(str, &i, result);
		else if (str[i] == '$')
			result = handle_variable_expand(str, &i, result, shell);
		else
			result = append_char_to_str(result, str[i++]);
	}
	return (result);
}
