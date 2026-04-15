/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:39:09 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/07/27 13:39:10 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

volatile sig_atomic_t	g_ack_received;

void	ack_handler(int signo)
{
	(void)signo;
	g_ack_received = 1;
}

void	send_bit(pid_t server_pid, int bit)
{
	g_ack_received = 0;
	if (bit)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
}

void	send_byte(pid_t server_pid, unsigned char byte)
{
	int	i;
	int	bit;

	i = 7;
	g_ack_received = 0;
	while (i >= 0)
	{
		bit = (byte >> i) & 1;
		send_bit(server_pid, bit);
		while (!g_ack_received)
			pause();
		i--;
		usleep(300);
	}
}

void	send_string(pid_t server_pid, char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		send_byte(server_pid, (unsigned char)str[i]);
		i++;
	}
	send_byte(server_pid, '\n');
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*a;

	if (argc != 3)
	{
		ft_printf("pid 와 보낼 문자열을 정확하게 입력해주세요");
		exit(0);
	}
	signal(SIGUSR1, ack_handler);
	server_pid = (pid_t)ft_atoi(argv[1]);
	a = argv[2];
	send_string(server_pid, a);
	return (0);
}
