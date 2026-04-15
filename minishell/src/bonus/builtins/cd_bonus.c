/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
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
 * @brief Updates PWD and OLDPWD environment variables
 * @param shell Shell state with environment
 * @param old_pwd Previous working directory
 */
static void	update_pwd(t_shell *shell, char *old_pwd)
{
	char	new_pwd[1024];

	if (old_pwd)
		set_env_value(&shell->env, "OLDPWD", old_pwd, 1);
	if (getcwd(new_pwd, sizeof(new_pwd)))
		set_env_value(&shell->env, "PWD", new_pwd, 1);
}

/**
 * @brief Handles cd - (go to OLDPWD)
 * @param shell Shell state with environment
 * @return OLDPWD value, NULL on error
 */
static char	*handle_cd_minus(t_shell *shell)
{
	char	*target;

	target = get_env_value(shell->env, "OLDPWD");
	if (!target)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	printf("%s\n", target);
	return (target);
}

/**
 * @brief Gets target directory for cd command
 * @param shell Shell state with environment
 * @param args Command arguments
 * @return Target directory path, NULL on error
 * @details Defaults to HOME if no argument given, - goes to OLDPWD
 */
static char	*get_target_dir(t_shell *shell, char **args)
{
	char	*target;

	if (!args[1] || (args[1][0] == '-' && args[1][1] == '-' && !args[1][2]))
	{
		target = get_env_value(shell->env, "HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (target);
	}
	if (args[1][0] == '-' && !args[1][1])
		return (handle_cd_minus(shell));
	return (args[1]);
}

/**
 * @brief Implements cd builtin command
 * @param shell Shell state with environment
 * @param args Command arguments (args[1] = target dir or NULL for HOME)
 * @return 0 on success, 1 on error
 * @details Updates PWD and OLDPWD environment variables
 */
int	builtin_cd(t_shell *shell, char **args)
{
	char	*target;
	char	old_pwd[1024];
	char	*old_pwd_value;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	target = get_target_dir(shell, args);
	if (!target)
		return (1);
	old_pwd_value = NULL;
	if (getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd_value = old_pwd;
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	update_pwd(shell, old_pwd_value);
	return (0);
}
