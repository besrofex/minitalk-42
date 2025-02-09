/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:48:21 by ylabser           #+#    #+#             */
/*   Updated: 2025/02/09 18:48:21 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char current_char = 0;
static int bit_count = 0;
static int message_received = 0;

void signal_handler(int sig)
{
    if (sig == SIGUSR1)
        current_char |= (1 << (7 - bit_count));
    bit_count++;
    if (bit_count == 8)
	 {
        if (current_char == '\0')
		  {
            message_received = 1;
            write(1, "\n", 1);
        }
		  else
            ft_printf("%c", current_char);
        current_char = 0;
        bit_count = 0;
    }
}

int main()
{
    struct sigaction sa;

    ft_printf("Serveur lancé avec le PID : %d\n", getpid());
    sa.sa_flags = 0;
    sa.sa_handler = signal_handler;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
        return (write(2, "Erreur avec sigaction.\n", 24), 1);
    while (1)
	 {
        while (!message_received)
            pause();
        message_received = 0;
    }
    return 0;
}
