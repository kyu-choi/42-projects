/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/stat.h>

/**
 * @brief Executes command in child process
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @param path Full path to executable
 * @details Calls execve and handles errors, never returns on success
 */
static void	execute_child(t_shell *shell, t_cmd *cmd, char *path)
{
	char		**envp;
	struct stat	path_stat;

	setup_signals_child();
	envp = env_to_array_util(shell->env);
	execve(path, cmd->args, envp);
	ft_free_split(envp);
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	if (access(path, X_OK) == -1 && errno == EACCES)
	{
		perror("minishell");
		exit(126);
	}
	perror("minishell");
	exit(127);
}

/**
 * @brief Updates the _ environment variable with command path
 * @param shell Shell state with environment
 * @param path Command path (relative or absolute)
 * @details Converts relative paths to absolute before setting
 */
static void	update_underscore(t_shell *shell, char *path)
{
	char	*abs_path;
	char	cwd[4096];

	if (!path)
		return ;
	if (path[0] == '/')
		abs_path = ft_strdup(path);
	else
	{
		if (!getcwd(cwd, sizeof(cwd)))
			return ;
		abs_path = ft_strjoin(cwd, "/");
		if (!abs_path)
			return ;
		path = ft_strjoin(abs_path, path);
		free(abs_path);
		abs_path = path;
	}
	set_env_value(&shell->env, "_", abs_path, 1);
	free(abs_path);
}

/**
 * @brief Executes an external command in a forked child process
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @return Exit status of command
 */
int	execute_external_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;

	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	update_underscore(shell, path);
	pid = fork();
	if (pid == 0)
		execute_child(shell, cmd, path);
	return (wait_and_get_status(pid, path));
}

/**
 * @brief Executes a simple (non-pipeline) command
 * @param shell Shell state
 * @param cmd Command to execute
 * @return Exit status of command
 * @details Handles builtins in current process, externals in child
 */
int	execute_simple_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[0] && is_assignment(cmd->args[0]))
		return (handle_assignment(cmd->args[0], shell));
	return (exec_with_redir(shell, cmd));
}

/**
 * @brief Main execution dispatcher for command list
 * @param shell Shell state
 * @param cmds Command list to execute
 * @return Exit status of last command
 * @details Handles pipelines, simple commands, and redirection-only commands
 */
int	execute(t_shell *shell, t_cmd *cmds)
{
	if (!cmds || !cmds->args)
		return (0);
	if (prepare_heredocs(cmds, shell) < 0)
		return (1);
	if (cmds->next)
		return (execute_pipeline(shell, cmds));
	if (!cmds->args[0])
		return (execute_redir_only(cmds, shell));
	if (!cmds->args[0][0])
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		return (127);
	}
	return (execute_simple_cmd(shell, cmds));
}
