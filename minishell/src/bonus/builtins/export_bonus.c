/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Handles export with = sign (KEY=VALUE)
 * @param shell Shell state with environment
 * @param arg Full argument string
 * @param key Variable key (freed by function)
 * @param equal Pointer to = character
 * @return 0 on success, 1 on error
 * @details Handles both normal export and += append operation
 */
static int	handle_key_with_equal(t_shell *shell, char *arg,
				char *key, char *equal)
{
	char	*value;

	if (ft_strlen(key) > 0 && key[ft_strlen(key) - 1] == '+')
		return (handle_append_export(shell, arg, key, equal));
	if (!is_valid_identifier(key))
	{
		free(key);
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	value = equal + 1;
	set_env_value(&shell->env, key, value, 1);
	free(key);
	return (0);
}

/**
 * @brief Exports or updates a variable
 * @param shell Shell state with environment
 * @param arg Argument in format KEY or KEY=VALUE
 * @return 0 on success, 1 on error
 * @details Creates variable without value if no = present
 */
static int	export_var(t_shell *shell, char *arg)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (!is_valid_identifier(arg))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		set_env_value(&shell->env, arg, NULL, 1);
		return (0);
	}
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	return (handle_key_with_equal(shell, arg, key, equal));
}

/**
 * @brief Processes one export argument
 * @param shell Shell state with environment
 * @param arg Argument to process
 * @return 0 on success, 1 on error, 2 on invalid option
 * @details Validates options and calls export_var
 */
static int	process_export_arg(t_shell *shell, char *arg)
{
	char	*eq;

	if (arg[0] == '-' && arg[1])
	{
		eq = ft_strchr(arg, '=');
		if ((eq && (eq - arg) > 1) || !eq)
		{
			ft_putstr_fd("minishell: export: -", 2);
			ft_putchar_fd(arg[1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (2);
		}
	}
	if (export_var(shell, arg))
		return (1);
	return (0);
}

/**
 * @brief Implements export builtin command
 * @param shell Shell state with environment
 * @param args Command arguments (args[0] = "export")
 * @return 0 on success, 1 if any variable failed, 2 on invalid option
 * @details Displays all variables if no args, otherwise exports each arg
 */
int	builtin_export(t_shell *shell, char **args)
{
	int		i;
	int		ret;
	int		res;

	if (!args[1])
		return (print_all_exports(shell->env), 0);
	i = 1;
	ret = 0;
	while (args[i])
	{
		res = process_export_arg(shell, args[i]);
		if (res == 2)
			return (2);
		if (res == 1)
			ret = 1;
		i++;
	}
	return (ret);
}
