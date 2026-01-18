/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:28:16 by florianh          #+#    #+#             */
/*   Updated: 2026/01/18 14:01:37 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// with start prints its PID
// waits for a signal
// check what signal we got and add it
// if we got all 8bits we write and reset for the next set of 8 till we got everything

#include "minitalk.h"

int main(void)
{
    // Implementation of server logic
    pid_t pid = getpid();
    ft_printf("Server PID: %d\n", pid);

    while (1)
    {
        pause(); // Wait for signals
    }
    return 0;
}
