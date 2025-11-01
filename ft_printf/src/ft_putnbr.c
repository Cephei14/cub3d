/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafik <rafik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:21:12 by rafik             #+#    #+#             */
/*   Updated: 2024/11/20 14:07:48 by rafik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	do_putnbr(int n)
{
	int	counter;

	counter = 0;
	if (n >= 10)
		counter += do_putnbr(n / 10);
	counter += ft_putchar((n % 10) + '0');
	return (counter);
}

int	ft_putnbr(va_list print_args)
{
	int	n;
	int	counter;

	n = va_arg(print_args, int);
	counter = 0;
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		counter += ft_putchar('-');
		n = -n;
	}
	counter += do_putnbr(n);
	return (counter);
}
