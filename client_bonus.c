/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:54:50 by hceviz            #+#    #+#             */
/*   Updated: 2025/02/02 22:09:03 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*if sigaction is initialized after sending signals,
it will cause a problem because program doesnt know how to handle them
when their acknowledge comes back*/
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

void	send_chr(int pid, char chr)
{
	int	bit_index;
	int	bit;

	bit_index = 8;
	while (bit_index--)
	{
		bit = (chr >> bit_index) & 1;
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

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (SIGUSR2 == signal)
		ft_printf("Message is received by server🚀🔥\n");
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		sigemptyset(&sa.sa_mask);
		sigaddset(&sa.sa_mask, SIGUSR2);
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
		sigaction(SIGUSR2, &sa, NULL);
		send_str(pid, av[2]);
		send_chr(pid, '\0');
		while (1)
			;
	}
	else
		ft_printf("Missing or wrong parameters!");
	return (1);
}
