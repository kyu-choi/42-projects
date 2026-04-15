/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "libft.h"

/**
 * @brief Executes external command in child process
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @param path Full path to executable
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
		ft_putstr_fd(": Is a directory\n", 2);
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
 * @brief Executes external (non-builtin) command
 * @param shell Shell state with environment
 * @param cmd Command to execute
 * @return Exit status of command
 * @details Finds command path, forks, executes, waits for child
 */
static int	execute_external(t_shell *shell, t_cmd *cmd)
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
	pid = fork();
	if (pid == 0)
		execute_child(shell, cmd, path);
	return (wait_and_get_status(pid, path));
}

/**
 * @brief Executes single command with redirections
 * @param shell Shell state with environment
 * @param cmd Single command to execute
 * @return Command exit status
 * @details Applies redirections, executes builtin or external
 */
int	execute_simple_cmd(t_shell *shell, t_cmd *cmd)
{
	int		stdin_backup;
	int		stdout_backup;
	int		ret;

	if (cmd->args[0] && is_assignment(cmd->args[0]))
		return (handle_assignment(cmd->args[0], shell));
	if (cmd->is_background)
		return (execute_background(shell, cmd));
	if (cmd->is_subshell)
		return (execute_subshell_cmd(cmd->subshell_tokens, shell));
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirs, shell) < 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		ret = execute_builtin(shell, cmd);
	else
		ret = execute_external(shell, cmd);
	restore_fds(stdin_backup, stdout_backup);
	return (ret);
}

/**
 * @brief Executes redirections without command
 * @param cmd Command with only redirections
 * @param shell Shell state for variable expansion
 * @return 0 on success, 1 on error
 */
static int	execute_redir_only(t_cmd *cmd, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	ret = apply_redirections(cmd->redirs, shell);
	restore_fds(stdin_backup, stdout_backup);
	if (ret < 0)
		return (1);
	return (0);
}

/**
 * @brief Main execution dispatcher
 * @param shell Shell state with environment
 * @param cmds Command pipeline to execute
 * @return Exit status of last command
 * @details Routes to pipeline or simple execution based on command count
 */
int	execute(t_shell *shell, t_cmd *cmds)
{
	if (!cmds || !cmds->args)
		return (0);
	if (prepare_heredocs(cmds, shell) < 0)
		return (1);
	if (cmds->next)
		return (execute_pipeline(shell, cmds));
	if (cmds->is_subshell)
		return (execute_simple_cmd(shell, cmds));
	if (!cmds->args[0])
		return (execute_redir_only(cmds, shell));
	if (!cmds->args[0][0])
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		return (127);
	}
	return (execute_simple_cmd(shell, cmds));
}
