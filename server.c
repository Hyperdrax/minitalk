/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:28:16 by florianh          #+#    #+#             */
/*   Updated: 2026/01/18 14:31:03 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// with start prints its PID
// waits for a signal
// check what signal we got and add it
// if we got all 8bits we write and reset for the next set of 8 till we got everything

#include "minitalk.h"

static void handle_signal(int sig)
{
    static int bit_count = 0;
    static char current_char = 0;

    if (sig == SIGUSR1)
        current_char |= (1 << bit_count);
    bit_count++;
    if (bit_count == 8)
    {
        write(1, &current_char, 1);
        bit_count = 0;
        current_char = 0;
    }
}

int main(void)
{
    // Implementation of server logic
    pid_t pid = getpid();

    ft_printf("Server PID: %d\n", pid);
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    while (1)
    {
        pause(); // Wait for signals
    }
    return 0;
}
