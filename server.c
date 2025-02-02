/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:33:30 by hceviz            #+#    #+#             */
/*   Updated: 2025/02/02 22:07:39 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//be careful with arguments quotation marks
void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static int	bitcount;
	static char	chr;

	(void)info;
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
	sa.sa_flags = 0;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	ft_printf("PID=%d\n", getpid());
	while (1)
		;
	return (1);
}
