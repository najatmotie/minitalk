/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:10 by nmotie-           #+#    #+#             */
/*   Updated: 2024/08/31 22:37:05 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	r;

	sign = 1;
	i = 0;
	r = 0;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * sign);
}

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 0;
	temp_char = character;
	while (i < 8)
	{
		temp_char = character >> i;
		if (temp_char % 2 == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]);
		message = av[2];
		i = 0;
		while (message[i])
		{
			send_signal(server_pid, message[i]);
			i++;
		}
		return (0);
	}
}
