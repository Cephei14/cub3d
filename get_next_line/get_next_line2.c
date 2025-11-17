/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:19:34 by rafik             #+#    #+#             */
/*   Updated: 2025/11/17 13:22:12 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

char	*handle_bonus_free(char **container)
{
	if (*container)
		free(*container);
	*container = NULL;
	return (NULL);
}

char	*handle_eof(char **container)
{
	char	*buffer;

	if (!*container || !**container)
	{
		free(*container);
		*container = NULL;
		return (NULL);
	}
	buffer = ft_strdup(*container);
	free(*container);
	*container = NULL;
	return (buffer);
}
