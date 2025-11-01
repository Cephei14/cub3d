/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/01 16:47:13 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_check(t_game *game, int n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while(game->data[0][i] == ' ')
		i++;
	while(game->data[n][k] == ' ')
		k++;
	while (game->data[0][i] || game->data[n][k])
	{
		if (game->data[0][i] != '1' || game->data[n][k] != '1')
			return (ft_printf("Error\nMap is not enclosed by walls\n"), FAIL);
		i++;
	}
	i = 1;
	while(game->data[i] && i < n)
	{
		j = ft_strlen(game->data[i]);
		if (game->data[i][0] != '1' || game->data[i] != '1')
			return (ft_printf("Error\nMap is not enclosed by walls\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}

int map_check(t_game *game, char *str)
{
	int n;
	
	while(game->data[n])
		n++;
	wall_check(str, n);
	return SUCCESS;
}

int	get_line_length(const char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (len - 1);
	return (len);
}

int	get_map_dimensions(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_printf("Error\nMap is empty\n"), FAIL);
	game->width = get_line_length(line);
	game->height = 0;
	while (line)
	{
		game->height++;
		if (get_line_length(line) != game->width)
		{
			free(line);
			return (ft_printf("Error\nMap is not rectangular\n"), FAIL);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (game->width == 0)
		return (ft_printf("Error\nMap contains empty lines\n"), FAIL);
	return (SUCCESS);
}
