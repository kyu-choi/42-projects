/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:10:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/10/05 23:10:00 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Executes command in background
 * @param shell Shell state with environment
 * @param cmd Command to execute in background
 * @return 0 (background processes don't wait)
 */
int	execute_background(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		setup_signals_child();
		if (apply_redirections(cmd->redirs, shell) < 0)
			exit(1);
		if (is_builtin(cmd->args[0]))
			exit(execute_builtin(shell, cmd));
		path = find_command_path(cmd->args[0], shell->env);
		if (!path)
			exit(127);
		envp = env_to_array_util(shell->env);
		execve(path, cmd->args, envp);
		exit(127);
	}
	return (0);
}
