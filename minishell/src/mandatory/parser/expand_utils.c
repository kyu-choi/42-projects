/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 09:36:09 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Appends single character to string
 * @param result String to append to (freed by function)
 * @param c Character to append
 * @return Newly allocated string with character appended
 */
char	*append_char_to_str(char *result, char c)
{
	char	ch[2];
	char	*tmp;

	ch[0] = c;
	ch[1] = '\0';
	tmp = ft_strjoin(result, ch);
	free(result);
	return (tmp);
}

/**
 * @brief Handles single quote section (no expansion)
 * @param str Input string
 * @param i Pointer to current index (at opening ', updated after closing ')
 * @param result Current result string
 * @return Updated result with literal content including quotes
 * @details Copies quote and content literally (quotes kept for remove_quotes)
 */
char	*handle_single_quote_expand(char *str, int *i, char *result)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		result = append_char_to_str(result, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

/**
 * @brief Handles variable expansion and appends to result
 * @param str Input string
 * @param i Pointer to current index (at $, updated after var)
 * @param res Current result string (freed by function)
 * @param shell Shell state with environment
 * @return Updated result with expanded variable
 */
char	*handle_variable_expand(char *str, int *i, char *res, t_shell *shell)
{
	char	*expanded;
	char	*tmp;

	expanded = expand_variable_in_str(str, i, shell);
	tmp = ft_strjoin(res, expanded);
	free(res);
	free(expanded);
	return (tmp);
}

/**
 * @brief Handles backslash escape sequences
 * @param str Input string
 * @param i Pointer to current index (at \)
 * @param res Current result string
 * @param in_dq In double quote flag
 * @return Updated result string
 */
char	*handle_backslash(char *str, int *i, char *res, int in_dq)
{
	(*i)++;
	if (!str[*i])
		return (append_char_to_str(res, '\\'));
	if (!in_dq)
	{
		if (str[*i] == '$' || str[*i] == '"' || str[*i] == '\\')
			return (append_char_to_str(res, str[(*i)++]));
		res = append_char_to_str(res, '\\');
		return (append_char_to_str(res, str[(*i)++]));
	}
	if (str[*i] == '$' || str[*i] == '"' || str[*i] == '\\')
		return (append_char_to_str(res, str[(*i)++]));
	res = append_char_to_str(res, '\\');
	return (append_char_to_str(res, str[(*i)++]));
}

/**
 * @brief Expands tilde to HOME directory
 * @param i Pointer to current index (at ~)
 * @param res Current result string
 * @param shell Shell state with environment
 * @param str Input string
 * @return Updated result with expanded tilde or literal ~
 * @details Expands only if ~ is alone or followed by / or whitespace
 */
char	*handle_tilde_expand(int *i, char *res, t_shell *shell, char *str)
{
	char	*home;
	char	*tmp;

	if (str[*i + 1] && str[*i + 1] != ' ' && str[*i + 1] != '/')
		return (append_char_to_str(res, str[(*i)++]));
	(*i)++;
	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (append_char_to_str(res, '~'));
	tmp = ft_strjoin(res, home);
	free(res);
	return (tmp);
}
