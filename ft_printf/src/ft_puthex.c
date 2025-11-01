/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafik <rafik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:21:00 by rafik             #+#    #+#             */
/*   Updated: 2024/11/20 13:34:05 by rafik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_puthex_recursive(unsigned int n, const char *base)
{
	int	counter;

	counter = 0;
	if (n >= 16)
		counter += ft_puthex_recursive(n / 16, base);
	counter += ft_putchar(base[n % 16]);
	return (counter);
}

int	ft_puthex(va_list print_args)
{
	unsigned int	num;
	const char		*base;
	int				counter;

	counter = 0;
	base = "0123456789abcdef";
	num = va_arg(print_args, unsigned int);
	if (num == 0)
	{
		ft_putchar('0');
		return (1);
	}
	counter = ft_puthex_recursive(num, base);
	return (counter);
}
