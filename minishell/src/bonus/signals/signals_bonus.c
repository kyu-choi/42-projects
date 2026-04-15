/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 01:41:23 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/**
 * @brief Signal handler for SIGINT (Ctrl-C)
 * @param sig Signal number (unused)
 * @details Sets global flag, prints newline, resets readline prompt
 */
static void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	ft_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Sets up signal handlers for interactive mode
 * @details SIGINT: custom handler, SIGQUIT: ignored, SIGCHLD: reaper
 */
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Sets up signal handlers for child processes
 * @details Restores default handlers for SIGINT and SIGQUIT
 */
void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief Sets up signal handlers during command execution
 * @details Parent ignores signals while child runs
 */
void	setup_signals_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
