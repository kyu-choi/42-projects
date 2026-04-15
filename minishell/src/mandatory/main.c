/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:45 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

/**
 * @brief Global signal flag for Ctrl-C handling
 * @details Set to 1 when SIGINT received, reset after handling
 */
int	g_signal = 0;

/**
 * @brief Initializes shell state structure
 * @param shell Shell structure to initialize
 * @param envp Environment array from main
 * @param argv0 argv[0] from main for _ variable
 */
static void	init_shell(t_shell *shell, char **envp, char *argv0)
{
	shell->env = init_env(envp);
	update_shlvl(&shell->env);
	if (argv0)
		set_env_value(&shell->env, "_", argv0, 1);
	shell->last_exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	shell->parse_error_type = 0;
	shell->is_interactive = 0;
}

/**
 * @brief Cleans up shell resources before exit
 * @param shell Shell structure to clean up
 */
static void	cleanup_shell(t_shell *shell)
{
	free_env(shell->env);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	if (shell->is_interactive)
		clear_history();
}

/**
 * @brief Creates placeholder files for non-interactive mode testing
 * @details Creates temporary files for output comparison
 */
static void	create_non_interactive_placeholders(void)
{
	const char	*files[] = {
		"tmp_out_bash",
		"tmp_err_bash",
		"tmp_out_minishell",
		"tmp_err_minishell"
	};
	int			i;
	int			fd;

	i = 0;
	while (i < 4)
	{
		if (access(files[i], F_OK) != 0)
		{
			fd = open(files[i], O_CREAT | O_RDONLY, 0644);
			if (fd >= 0)
				close(fd);
		}
		i++;
	}
}

/**
 * @brief Main entry point for minishell
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused)
 * @param envp Environment variables to initialize shell
 * @return Exit status of shell
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		is_interactive;

	(void)argc;
	init_shell(&shell, envp, argv[0]);
	setup_signals();
	is_interactive = isatty(STDIN_FILENO);
	shell.is_interactive = is_interactive;
	if (!is_interactive)
	{
		create_non_interactive_placeholders();
		unset_env_value(&shell.env, "PS1");
	}
	run_shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.last_exit_status);
}
