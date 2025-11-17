/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:19:25 by rafik             #+#    #+#             */
/*   Updated: 2025/11/17 13:22:03 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE > 99999999 || BUFFER_SIZE <= 0
#  error "BUFFER_SIZE must be greater than 0 and less than or equal to 99999999"
# endif

char	*get_next_line(int fd);
char	*handle_eof(char **container);
char	*handle_bonus_free(char **container);
int		ckeck(char *TempStr, char **container, char **Buffer);
char	*fill_buffer(char *TempStr, char *container, int i);
int		check_container(char **container, char **buffer);
char	*cut_container(char *TempStr, char *container, int j);

#endif
