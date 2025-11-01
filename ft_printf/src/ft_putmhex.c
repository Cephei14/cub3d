/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafik <rafik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:55:23 by rafik             #+#    #+#             */
/*   Updated: 2024/11/20 13:57:17 by rafik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_putmhex_recursive(unsigned int n, const char *base)
{
	int	counter;

	counter = 0;
	if (n >= 16)
		counter += ft_putmhex_recursive(n / 16, base);
	counter += ft_putchar(base[n % 16]);
	return (counter);
}

int	ft_putmhex(va_list print_args)
{
	unsigned int	num;
	const char		*base;
	int				counter;

	counter = 0;
	base = "0123456789ABCDEF";
	num = va_arg(print_args, unsigned int);
	if (num == 0)
	{
		ft_putchar('0');
		return (1);
	}
	counter = ft_putmhex_recursive(num, base);
	return (counter);
}
