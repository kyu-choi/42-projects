/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 00:11:18 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks if command is a builtin
 * @param cmd Command name to check
 * @return 1 if builtin (echo, cd, pwd, export, unset, env, exit), 0 otherwise
 */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, ".", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "history", 8) == 0)
		return (1);
	return (0);
}

/**
 * @brief Executes builtin command
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @return Exit status of builtin
 * @details Dispatches to appropriate builtin function
 */
int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], ".", 2) == 0)
		return (builtin_source(cmd, shell));
	if (ft_strncmp(cmd->args[0], "history", 8) == 0)
		return (builtin_history(cmd->args));
	return (1);
}
