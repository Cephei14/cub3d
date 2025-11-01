/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:17:44 by rafik             #+#    #+#             */
/*   Updated: 2025/05/08 11:22:03 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(int *i, const char *format,
		va_list print_args, t_prnt *handlers)
{
	int	j;
	int	l;

	(*i)++;
	l = 0;
	j = 0;
	while (j <= 7)
	{
		if (format[*i] == handlers[j].c)
		{
			l += handlers[j].ft(print_args);
			break ;
		}
		j++;
	}
	if (j == 8)
		l += ft_putchar(format[*i]);
	return (l);
}

int	check_format(const char *format, va_list print_args,
		t_prnt *handlers, int *l)
{
	int	i;

	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
			(*l) += ft_putchar(format[i]);
		else
			(*l) += handle_format(&i, format, print_args, handlers);
		i++;
	}
	return (*l);
}

int	ft_printf(const char *format, ...)
{
	int		l;
	va_list	print_args;
	t_prnt	handlers[8];

	handlers[0] = (t_prnt){'i', ft_putnbr};
	handlers[1] = (t_prnt){'d', ft_putnbr};
	handlers[2] = (t_prnt){'u', ft_putnbru};
	handlers[3] = (t_prnt){'x', ft_puthex};
	handlers[4] = (t_prnt){'X', ft_putmhex};
	handlers[5] = (t_prnt){'p', ft_putptr};
	handlers[6] = (t_prnt){'c', ft_printchar};
	handlers[7] = (t_prnt){'s', ft_putstr};
	l = 0;
	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(print_args, format);
	l = check_format(format, print_args, handlers, &l);
	va_end(print_args);
	return (l);
}
