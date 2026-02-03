/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:28:23 by flhensel          #+#    #+#             */
/*   Updated: 2026/02/03 14:15:24 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	g_client = {0, 0};

void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		g_client.bit_confirmed = 1;
	else if (signal == SIGUSR2)
		g_client.message_confirmed = 1;
	else
		ft_printf("Warning: Unexpected signal received: %d\n", signal);
}

void	ft_send_signal(int pid, char c, int *bit)
{
	int	signal;
	int	retries;

	if (((c >> *bit) & 1) == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_printf("Error: Failed to send signal to server\n");
		exit(EXIT_FAILURE);
	}
	retries = 1000;
	while (!g_client.bit_confirmed && retries-- > 0)
		usleep(100);
	if (!g_client.bit_confirmed)
	{
		ft_printf("Error: No acknowledgment received from server.\n");
		exit(EXIT_FAILURE);
	}
	g_client.bit_confirmed = 0;
}

void	ft_send_message(int pid, char *msg)
{
	int		bit;
	int		i;
	char	c;
	int		len;

	i = 0;
	len = ft_strlen(msg) + 1;
	while (i < len)
	{
		bit = 7;
		c = msg[i];
		while (bit >= 0)
		{
			g_client.bit_confirmed = 0;
			ft_send_signal(pid, c, &bit);
			bit--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Error: The correct format is %s <PID> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_send_message(pid, argv[2]);
	while (!g_client.message_confirmed)
		pause();
	ft_printf("✅ Message delivered!\n");
	return (0);
}
