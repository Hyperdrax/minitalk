/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:28:16 by florianh          #+#    #+#             */
/*   Updated: 2026/02/03 14:10:46 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_buffer
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_buffer;

static char	*grow_buffer(t_buffer *buf)
{
	char	*tmp;
	size_t	new_cap;
	size_t	i;

	new_cap = 1024;
	if (buf->cap)
		new_cap = buf->cap * 2;
	tmp = malloc(new_cap);
	if (!tmp)
	{
		free(buf->data);
		buf->data = NULL;
		buf->len = 0;
		buf->cap = 0;
		ft_printf("Error: Failed to grow buffer.\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < buf->len)
		tmp[i] = buf->data[i];
	free(buf->data);
	buf->cap = new_cap;
	return (tmp);
}

static void	append_char(t_buffer *buf, char c)
{
	if (buf->len + 1 >= buf->cap)
		buf->data = grow_buffer(buf);
	buf->data[buf->len++] = c;
	buf->data[buf->len] = '\0';
}

static void	process_byte(siginfo_t *info, t_buffer *msg, char c)
{
	append_char(msg, c);
	if (c == '\0')
	{
		if (msg->data)
			ft_printf("%s\n", msg->data);
		free(msg->data);
		msg->data = NULL;
		msg->len = 0;
		msg->cap = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_printf("Error: Failed to send confirmation message.\n");
	}
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int		bit_acc;
	static int		bit_count;
	static t_buffer	message;

	(void)context;
	bit_acc = bit_acc << 1;
	if (signal == SIGUSR1)
		bit_acc |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		process_byte(info, &message, (char)bit_acc);
		bit_acc = 0;
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_printf("Error: Failed to send confirmation char.\n");
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server's ID : %d\n", getpid());
	ft_printf("Waiting for a message...\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
