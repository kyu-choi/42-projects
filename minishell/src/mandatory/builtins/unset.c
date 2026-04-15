/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/21 00:51:57 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Implements unset builtin command
 * @param shell Shell state with environment
 * @param args Command arguments (variable names to unset)
 * @return 0 on success, 2 on invalid option
 * @details Removes each specified variable from environment
 */
int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1])
		{
			ft_putstr_fd("minishell: unset: -", 2);
			ft_putchar_fd(args[i][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
			return (2);
		}
		unset_env_value(&shell->env, args[i]);
		i++;
	}
	return (0);
}
