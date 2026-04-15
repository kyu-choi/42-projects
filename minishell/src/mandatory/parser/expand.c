/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
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
 * @brief Calculates variable name length
 * @param str String starting at variable name
 * @return Length of variable name (alphanumeric + underscore)
 * @details Special case: ? returns 1
 */
static int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/**
 * @brief Gets value of environment variable
 * @param var_name Variable name to look up
 * @param shell Shell state with environment
 * @return Variable value (newly allocated), empty string if not found
 * @details Special case: ? returns last exit status
 */
static char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*value;
	char	*exit_str;

	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		exit_str = ft_itoa(shell->last_exit_status);
		return (exit_str);
	}
	value = get_env_value(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

/**
 * @brief Expands single variable at position
 * @param str Input string
 * @param i Pointer to current index (at $, updated after var)
 * @param shell Shell state with environment
 * @return Expanded variable value (newly allocated)
 * @details Handles $VAR, $?, and edge cases like $ alone
 */
char	*expand_variable_in_str(char *str, int *i, t_shell *shell)
{
	int		var_len;
	char	*var_name;
	char	*value;

	(*i)++;
	if (str[*i] == '\0')
		return (ft_strdup("$"));
	if (str[*i] == '\'')
		return (ft_strdup(""));
	var_len = get_var_len(&str[*i]);
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str, *i, var_len);
	value = get_var_value(var_name, shell);
	free(var_name);
	*i += var_len;
	return (value);
}

/**
 * @brief Processes quote character during expansion
 * @param str Input string
 * @param i Pointer to current index
 * @param res Current result string
 * @param in_dq Pointer to double-quote state flag
 * @return Updated result string
 */
static char	*proc_quote(char *str, int *i, char *res, int *in_dq)
{
	if (str[*i] == '\'' && !(*in_dq))
		return (handle_single_quote_expand(str, i, res));
	if (str[*i] == '"')
	{
		*in_dq = !(*in_dq);
		(*i)++;
		return (res);
	}
	res = append_char_to_str(res, str[(*i)++]);
	return (res);
}

/**
 * @brief Expands all variables in string
 * @param str String containing variables ($VAR, $?)
 * @param shell Shell state with environment
 * @return Newly allocated string with expanded variables
 */
char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	int		i;
	int		in_dquote;

	result = ft_strdup("");
	i = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			result = proc_quote(str, &i, result, &in_dquote);
		else if (str[i] == '\\')
			result = handle_backslash(str, &i, result, in_dquote);
		else if (str[i] == '$')
			result = handle_variable_expand(str, &i, result, shell);
		else if (str[i] == '~' && i == 0)
			result = handle_tilde_expand(&i, result, shell, str);
		else
			result = append_char_to_str(result, str[i++]);
	}
	return (result);
}
