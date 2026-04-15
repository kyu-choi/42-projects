/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Validates identifier name for export
 * @param str String to validate
 * @return 1 if valid identifier, 0 otherwise
 */
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Handles append export (KEY+=VALUE)
 * @param shell Shell state with environment
 * @param arg Original argument string (for error messages)
 * @param key Key to append to (may have trailing '+')
 * @param equal Pointer to '=' character in arg
 * @return 0 on success, 1 on error
 */
int	handle_append_export(t_shell *shell, char *arg, char *key, char *equal)
{
	char	*old_val;
	char	*new_val;

	key[ft_strlen(key) - 1] = '\0';
	if (!is_valid_identifier(key))
	{
		free(key);
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	old_val = get_env_value(shell->env, key);
	if (old_val)
		new_val = ft_strjoin(old_val, equal + 1);
	else
		new_val = ft_strdup(equal + 1);
	if (!new_val)
		return (free(key), 1);
	set_env_value(&shell->env, key, new_val, 1);
	return (free(new_val), free(key), 0);
}
