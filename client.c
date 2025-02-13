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

static int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	long	res;

	i = 0;
	signe = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
				str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			signe = signe * -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - 48);
	}
	if ((signe == 1 && res > 2147483647)
		|| (signe == -1 && res > 2147483648))
		return (-100);
	if (str[i] != '\0')
		return (-100);
	return (res * signe);
}

static void	send_byte(int pid, char c)
{
	int	i;

	i = 128;
	while (i > 0)
	{
		if (c >= i)
		{
			kill(pid, SIGUSR2);
			c -= i;
		}
		else
			kill(pid, SIGUSR1);
		i /= 2;
		usleep(200);
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3 && ft_atoi(argv[1]) != -100
		&& ft_atoi(argv[1]) >= 0 && (kill(ft_atoi(argv[1]), 0) == 0))
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			send_byte(pid, argv[2][i]);
			i++;
		}
	}
	else
	{
		ft_printf("Error\n");
		return (1);
	}
	return (0);
}
