/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Handles append-style export (key+=value)
 * @param shell Shell state
 * @param arg Original argument string
 * @param key Variable key
 * @param equal Pointer to = character
 * @return 0 on success, 1 on error
 */
int	handle_append_export(t_shell *shell, char *arg, char *key, char *equal);

/**
 * @brief Handles export with equals sign (key=value or key+=value)
 * @param shell Shell state
 * @param arg Original argument string
 * @param key Variable key
 * @param equal Pointer to = character
 * @return 0 on success, 1 on error
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
 * @brief Exports single variable from argument
 * @param shell Shell state with environment
 * @param arg Argument in KEY=VALUE or KEY+=VALUE format (or just KEY)
 * @return 0 on success, 1 on error
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
 * @brief Processes a single export argument
 * @param shell Shell state
 * @param arg Argument to export
 * @return 0 on success, 1 on error or invalid option
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
 * @brief Builtin export command implementation
 * @param shell Shell state with environment
 * @param args Command arguments (args[0] is "export")
 * @return 0 on success, 1 if any argument fails, 2 if invalid option
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
