/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:19:43 by rafik             #+#    #+#             */
/*   Updated: 2025/06/06 18:54:19 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

char	*fill_buffer(char *tempstr, char *container, int i)
{
	char	*buffer;
	int		container_len;

	container_len = 0;
	if (container)
		container_len = ft_strlen(container);
	buffer = malloc(container_len + i + 2);
	if (!buffer)
		return (NULL);
	if (container)
		ft_strlcpy(buffer, container, container_len + 1);
	ft_strlcpy(buffer + container_len, tempstr, i + 2);
	return (buffer);
}

char	*cut_container(char *tempstr, char *container, int j)
{
	char	*new_container;

	new_container = ft_strdup(tempstr + j);
	free(container);
	return (new_container);
}

int	ckeck(char *tempstr, char **container, char **buffer)
{
	int	i;
	int	j;

	i = 0;
	while (tempstr[i])
	{
		if (tempstr[i] == '\n')
		{
			j = i + 1;
			*buffer = fill_buffer(tempstr, *container, i);
			if (!*buffer)
				return (-1);
			*container = cut_container(tempstr, *container, j);
			return (1);
		}
		i++;
	}
	*container = ft_strjoin(*container, tempstr);
	if (*container)
		return (0);
	return (-1);
}

int	read_file(int fd, char **container, char **buffer)
{
	char		*tempstr;
	ssize_t		bytes_read;
	int			result;

	tempstr = malloc(BUFFER_SIZE + 1);
	if (!tempstr)
		return (-1);
	bytes_read = read(fd, tempstr, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		tempstr[bytes_read] = '\0';
		result = ckeck(tempstr, container, buffer);
		if (result)
		{
			free(tempstr);
			return (1);
		}
		bytes_read = read(fd, tempstr, BUFFER_SIZE);
	}
	free(tempstr);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*buffer;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = NULL;
	if (check_container(&container, &buffer) == 1)
		return (buffer);
	if (read_file(fd, &container, &buffer))
		return (buffer);
	if (container && *container)
	{
		buffer = ft_strdup(container);
		free(container);
		container = NULL;
		return (buffer);
	}
	free(container);
	container = NULL;
	return (NULL);
}
