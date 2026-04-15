/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:17 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*resolve_env_path(t_shell *shell)
{
	char	*path;

	if (access("/usr/bin/env", X_OK) == 0)
		return (ft_strdup("/usr/bin/env"));
	path = find_command_path("env", shell->env);
	return (path);
}

/**
 * @brief Executes env command in child process
 * @param shell Shell state with environment
 * @param args Arguments for env command
 * @param path Path to env executable
 * @details Does not return, exits with status code
 */
static void	exec_env_child(t_shell *shell, char **args, char *path)
{
	char	**envp;

	setup_signals_child();
	envp = env_to_array_util(shell->env);
	execve(path, args, envp);
	ft_free_split(envp);
	perror("env");
	exit(127);
}

/**
 * @brief Executes env command with arguments in child process
 * @param shell Shell state with environment
 * @param args Command arguments
 * @return Exit status of env command
 */
static int	exec_env_command(t_shell *shell, char **args)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = resolve_env_path(shell);
	if (!path)
	{
		ft_putstr_fd("minishell: env: command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		free(path);
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_env_child(shell, args, path);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

/**
 * @brief Implements env builtin command
 * @param shell Shell state with environment
 * @param args Command arguments (optional command to execute)
 * @return 0 on success, command exit status otherwise
 * @details Prints all environment variables or executes command with env
 */
int	builtin_env(t_shell *shell, char **args)
{
	t_env	*env;

	if (args[1])
		return (exec_env_command(shell, args));
	env = shell->env;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
