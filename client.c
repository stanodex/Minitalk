/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:16:51 by hceviz            #+#    #+#             */
/*   Updated: 2025/02/02 22:00:31 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return ((int)(res * sign));
}

void	send_chr(int pid, char msg_chr)
{
	int	bitindex;
	int	bit;

	bitindex = 8;
	while (bitindex--)
	{
		bit = (msg_chr >> bitindex) & 1;
		if (bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(50);
	}
}

void	send_str(int pid, char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		send_chr(pid, msg[i]);
}

int	main(int ac, char **av)
{
	int	pid;

	pid = ft_atoi(av[1]);
	if (ac == 3)
	{
		send_str(pid, av[2]);
		send_chr(pid, '\0');
	}
	else
		ft_printf("Missing or wrong parameters!");
	return (0);
}
