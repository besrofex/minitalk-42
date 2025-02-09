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

static void	read_byte(int sign, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = 128;
	static int	current_client = 0;

	(void)context;
	if (current_client == 0)
		current_client = info->si_pid;
	if (current_client != info->si_pid)
	{
		ft_printf("\n");
		current_client = info->si_pid;
		c = 0;
		bit = 128;
	}
	if (sign == SIGUSR2)
		c += bit;
	bit /= 2;
	if (bit == 0)
	{
		ft_printf("%c", c);
		c = 0;
		bit = 128;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error\n");
		return (1);
	}
	sa.sa_sigaction = read_byte;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = getpid();
	ft_printf("%d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
