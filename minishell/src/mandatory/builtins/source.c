/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/21 22:10:34 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

/**
 * @brief Implements the '.' (source) builtin command
 * @param cmd Command structure containing arguments
 * @param shell Shell state (unused)
 * @return Always returns 2 (usage error)
 */
int	builtin_source(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	if (!cmd->args[1])
	{
		write(2, ".: usage: . filename [arguments]\n", 33);
		return (127);
	}
	return (0);
}
