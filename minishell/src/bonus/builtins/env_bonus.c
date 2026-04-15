/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 09:36:09 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_bonus.h"

/**
 * @brief Implements env builtin command
 * @param shell Shell state with environment
 * @param args Command arguments (should be NULL)
 * @return 0 on success, 127 if args present
 * @details Prints all environment variables in KEY=VALUE format
 */
int	builtin_env(t_shell *shell, char **args)
{
	t_env	*env;

	if (args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (127);
	}
	env = shell->env;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
