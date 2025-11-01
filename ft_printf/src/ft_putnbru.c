/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafik <rafik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:56:25 by rafik             #+#    #+#             */
/*   Updated: 2024/11/20 13:57:00 by rafik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	do_putnbru(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n >= 10)
		counter += do_putnbru(n / 10);
	counter += ft_putchar((n % 10) + '0');
	return (counter);
}

int	ft_putnbru(va_list print_args)
{
	int				counter;
	unsigned int	n;

	n = va_arg(print_args, unsigned int);
	counter = 0;
	counter += do_putnbru(n);
	return (counter);
}
