/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:38:25 by hceviz            #+#    #+#             */
/*   Updated: 2025/01/15 19:04:58 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//be careful with argument promotion
//promotion char to int
// pointers cant be promoted

/* print_c(*(s++)) is same with
vvvvvvvvvvvvvv
 print_c(*s)
 s++;
 */

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	print_s(char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	process_specifier(char flag, va_list ap)
{
	if (flag == 'd' || flag == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (flag == 'c')
		return (print_c(va_arg(ap, int)));
	else if (flag == 's')
		return (print_s(va_arg(ap, char *)));
	else if (flag == 'p')
		return (print_ptr(va_arg(ap, void *)));
	else if (flag == 'u')
		return (print_u(va_arg(ap, unsigned int)));
	else if (flag == 'x')
		return (print_hex(va_arg(ap, unsigned int), 1));
	else if (flag == 'X')
		return (print_hex(va_arg(ap, unsigned int), 0));
	else if (flag == '%')
		return (print_c((int)flag));
	else
		return (-1);
}

int	ft_printf(const char *flag, ...)
{
	va_list	ap;
	int		count;
	int		temp;

	va_start(ap, flag);
	count = 0;
	temp = 0;
	while (*flag)
	{
		temp = 0;
		if (*flag == '%')
		{
			temp = process_specifier(*(++flag), ap);
			if (temp == -1)
				return (-1);
			count += temp;
		}
		else
			count += print_c((*flag));
		flag++;
	}
	return (count);
}
