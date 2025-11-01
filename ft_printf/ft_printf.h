/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:42:04 by rafik             #+#    #+#             */
/*   Updated: 2025/04/21 14:15:20 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# define _POSIX_C_SOURCE 200809L

int	ft_putchar(char c);
int	ft_printf(const char *format, ...);
int	ft_putstr(va_list print_args);
int	ft_printchar(va_list print_args);
int	ft_putnbr(va_list print_args);
int	ft_putnbru(va_list print_args);
int	ft_puthex(va_list print_args);
int	ft_putmhex(va_list print_args);
int	ft_putptr(va_list print_args);

typedef struct handle
{
	char	c;
	int		(*ft)();
}	t_prnt;

#endif
