/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafik <rafik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:19:34 by rafik             #+#    #+#             */
/*   Updated: 2025/01/08 21:25:08 by rafik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src || !dest || n == 0)
		return (ft_strlen(src));
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	l1;
	size_t	l2;
	char	*str;

	i = -1;
	j = -1;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (l1 + l2) + 1);
	if (str == NULL)
		return (NULL);
	while (++i < l1)
		str[i] = s1[i];
	while (i < (l1 + l2))
	{
		str[i] = s2[++j];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int	check_container(char **container, char **buffer)
{
	int	i;

	if (!*container || !**container)
		return (0);
	i = 0;
	while ((*container)[i])
	{
		if ((*container)[i] == '\n')
		{
			*buffer = fill_buffer(*container, NULL, i);
			if (!*buffer)
				return (-1);
			*container = cut_container(*container, *container, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
