/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:04 by nmotie-           #+#    #+#             */
/*   Updated: 2024/08/31 23:18:49 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

void	handle_signal(int signal, siginfo_t *info, void *ucontext)
{
	static int	index_bit;
	static char	collected_byte;
	static int	last_sender;

	(void)ucontext;
	if (last_sender != info->si_pid)
	{
		index_bit = 0;
		collected_byte = 0;
		last_sender = info->si_pid;
	}
	if (signal == SIGUSR1)
		collected_byte = collected_byte | (1 << (index_bit));
	index_bit++;
	if (index_bit == 8)
	{
		write(1, &collected_byte, 1);
		index_bit = 0;
		collected_byte = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	write(1, "PID is: ", 8);
	ft_putnbr(pid);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
	return (0);
}
