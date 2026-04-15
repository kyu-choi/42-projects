/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks if string is a variable assignment (VAR=value)
 * @param str String to check
 * @return 1 if assignment pattern, 0 otherwise
 * @details Validates: starts with letter/_, contains =, valid identifier
 */
int	is_assignment(char *str)
{
	char	*equal;
	char	*key;
	int		result;

	if (!str || !*str)
		return (0);
	equal = ft_strchr(str, '=');
	if (!equal || equal == str)
		return (0);
	key = ft_substr(str, 0, equal - str);
	if (!key)
		return (0);
	result = is_valid_identifier(key);
	free(key);
	return (result);
}

/**
 * @brief Handles variable assignment (VAR=value)
 * @param str Assignment string (VAR=value format)
 * @param shell Shell state with environment
 * @return 0 on success, 1 on error
 * @details Sets variable in shell environment without export
 */
int	handle_assignment(char *str, t_shell *shell)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (1);
	key = ft_substr(str, 0, equal - str);
	if (!key)
		return (1);
	value = equal + 1;
	set_env_value(&shell->env, key, value, 0);
	free(key);
	return (0);
}
