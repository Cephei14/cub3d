/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/02 00:16:19 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int NS_wall_check(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if(line[i] != ' ' && line[i] != '1')
			return FAIL;
		i++;
	}
	return SUCCESS;
}

int EW_wall_check(char *line)
{
	int i;

	i = 0;
	while(line[i] == ' ')
		i++;
	if(line[i] != '1')
		return FAIL;
	while(line[i])
	{
		while(line[i] == '1' || line[i] == '0')
			i++;
		if(line[i] == ' ')
		{
			if(line[i - 1] != '1')
				return FAIL;
			i++;
			while(line[i] == ' ')
				i++;
			if(line[i] != '1')
				return FAIL;
		}
	}
	return i;
}

int parse_check(int fd, t_game *game)
{
	char *line;
	int i;

	line = get_next_line(fd);
	if(!line)
		return (printf("Empty file\n"), FAIL);
	game->data = malloc(sizeof(char *) + 1);
	game->data[0] = ft_strdup(line);
	if ((NS_wall_check(game->data[0])) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	i = 1;
	while(line = get_next_line(fd))
	{
		i++;
		if ((EW_wall_check(line)) == FAIL)
			return (printf("Map not surrounded by walls\n"), FAIL);
		ft_realloc(game->data, i + 1);
		game->data[i] = ft_strdup(line);
	}
	if ((NS_wall_check(game->data[i])) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	game->data[i + 1] = NULL;
	return i;
}

int open_file_parse(char *str, t_game *game)
{
	int fd;
	
	if ((fd = open(str, O_RDONLY)) < 0)
		return (printf("Error : Could not open file\n"), FAIL);
	if(parse_check(&game, str) == FAIL)
		return FAIL;
}
