/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:57:43 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/07/27 12:57:44 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

void	handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	ch;
	static int				bit_count;
	static pid_t			client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		ch = 0;
		bit_count = 0;
		client_pid = info->si_pid;
	}
	ch <<= 1;
	if (signo == SIGUSR2)
		ch |= 1;
	bit_count++;
	kill(client_pid, SIGUSR1);
	if (bit_count == 8)
	{
		write(1, &ch, 1);
		bit_count = 0;
		ch = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
