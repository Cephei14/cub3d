/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafik <rafik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:21:16 by rafik             #+#    #+#             */
/*   Updated: 2024/11/20 13:42:50 by rafik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	do_putptr(unsigned long n, const char *base)
{
	int	counter;

	counter = 0;
	if (n >= 16)
		counter += do_putptr(n / 16, base);
	counter += ft_putchar(base[n % 16]);
	return (counter);
}

int	ft_putptr(va_list print_args)
{
	unsigned long	ptr;
	const char		*base;
	int				counter;

	ptr = (unsigned long)va_arg(print_args, void *);
	counter = 0;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	else
	{
		base = "0123456789abcdef";
		counter += ft_putchar('0');
		counter += ft_putchar('x');
		counter += do_putptr(ptr, base);
	}
	return (counter);
}
