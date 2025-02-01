/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:12:34 by hceviz            #+#    #+#             */
/*   Updated: 2025/02/01 14:05:11 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static char	chr;
	static int	bitcount;

	(void)ucontext;
	if (signal == SIGUSR2)
		chr = (chr << 1) | 1;
	else if (signal == SIGUSR1)
		chr = (chr << 1);
	bitcount++;
	if (bitcount == 8)
	{
		bitcount = 0;
		if (chr == '\0')
		{
			write(1, "\n", 1);
			chr = 0;
			kill(info->si_pid, 12);
			usleep(50);
			return ;
		}
		write(1, &chr, 1);
		chr = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID=%d\n", getpid());
	while (1)
		;
	return (1);
}
