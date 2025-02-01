/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:34:18 by hceviz            #+#    #+#             */
/*   Updated: 2025/01/16 12:53:48 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*print_hex has case_flag parameter to avoid from
creating two functions for up and low case
=================================================
pointer address might be bigger
than int range that is why unsigned long
unsigned long because we are working on
memory unsigned provides pure address without sign*/

int	print_ptr(void *ptr)
{
	unsigned long	num;
	int				count;

	num = (unsigned long)ptr;
	if (!ptr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	if (num >= 16)
		count += print_hex(num, 1);
	else
		count += print_hex(num, 1);
	return (count);
}

int	print_c(int c)
{
	char	x;

	x = (char)c;
	write(1, &x, 1);
	return (1);
}

int	ft_putnbr(int num)
{
	int		count;
	char	number;

	count = 0;
	if (num == -2147483648)
		return (write(1, "-2147483648", 11));
	if (num < 0)
	{
		write(1, "-", 1);
		num *= -1;
		count++;
	}
	if (num < 10)
	{
		number = num + '0';
		write(1, &number, 1);
		count++;
	}
	else
	{
		count += ft_putnbr(num / 10);
		count += ft_putnbr(num % 10);
	}
	return (count);
}

int	print_u(unsigned int num)
{
	int	written;

	written = 0;
	if (num >= 10)
		written += print_u(num / 10);
	written += print_c((num % 10) + '0');
	return (written);
}

int	print_hex(unsigned long num, unsigned int case_flag)
{
	char			*base;
	long			written;

	written = 0;
	if (case_flag == 1)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (num >= 16)
		written = print_hex(num / 16, case_flag);
	print_c(base[num % 16]);
	return (written + 1);
}
