/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:28:23 by flhensel          #+#    #+#             */
/*   Updated: 2026/01/19 12:30:40 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int ft_atoi(const char *str)
{
	int num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

static void send_byte(pid_t pid, unsigned char byte)
{
	int j;

	j = 7;
	while (j >= 0)
	{
		if (byte >> j & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(300);
		j--;
	}
}

int main(int argc, char **argv)
{
	pid_t pid;
	int i;
	
	if (argc != 3)
	{
		write(2,"Usage: ./client <pid> <message>\n", 32);
		return(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(2,"Invalid PID\n",12);
		return(0);
	}

	i = 0;
	while (argv[2][i])
	{
		send_byte(pid, argv[2][i]);
		i++;
	}
	send_byte(pid, '\n');
	return(0);
}
