/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:49:09 by ylabser           #+#    #+#             */
/*   Updated: 2025/02/09 18:49:09 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_character(pid_t server_pid, char character)
{
	int	i;

	i = 0;
    while (i < 8)
	 {
        if (character & (1 << (7 - i)))
            kill(server_pid, SIGUSR1);
		  else
            kill(server_pid, SIGUSR2);
        usleep(100);
		  i++;
    }
}

void send_message(pid_t server_pid, const char *message)
{
    while (*message)
	 {
        send_character(server_pid, *message);
        message++;
    }
    send_character(server_pid, '\0');
}

int main(int argc, char *argv[])
{
	pid_t server_pid;
	const char *message;
	int i;

   if (argc != 3)
      return (write(2, "Invalide message or PID...\n", 28), 1);
	i = 0;
	while (argv[1][i])
	{
		if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
			return (write(2, "pid does not work", 18), 1);
		i++;
	}
   server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) != 0 || server_pid == 0 || !argv[2][0])
		return (write(2, "\033[31mpid or string does not work\033[0m", 37), 1);
   message = argv[2];
   send_message(server_pid, message);
   return (0);
}
