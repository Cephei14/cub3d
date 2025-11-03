/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/03 12:20:33 by rdhaibi          ###   ########.fr       */
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

int check(char c, int *player)
{
	if(c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player)++;
		return 1;
	}
	if(c == '1' || c == '0')
		return 1;
	if (c == '\0')
		return 0;
}

int EW_wall_check(char *line, int *player)
{
	int i;

	i = 0;
	while(line[i] == ' ')
		i++;
	if(line[i] != '1')
		return FAIL;
	while(line[i])
	{
		while(check(line[i], &player))
			i++;
		if (player > 1)
			return FAIL;
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

int grid(t_game *game, char *line, int *i)
{
	int player;

	game->grid = malloc(sizeof(char *) + 1);
	game->grid[0] = ft_strdup(line);
	if ((NS_wall_check(game->grid[0])) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	if ((EW_wall_check(line, &player)) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	ft_realloc(game->grid, (*i) + 1);
	game->grid[*i] = ft_strdup(line);
	if ((NS_wall_check(game->grid[*i])) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	game->grid[(*i) + 1] = NULL;
	i++;
}

int color_check(char *id, char *pth, int *arr, t_game *game)
{
	char *color;
	int i;

	i = -1;
	color = ft_split(pth, ',');
	while(color[++i])
	{
		if(ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255 || i >= 3)
			return(free(color), FAIL);
	}
	if(i != 2)
		return (free(color), FAIL);
	if (id == 'F')
	{
		arr[4]++;
		game->floor_color = ft_strdup(pth);
	}
	else if (id == 'C')
	{
		arr[5]++;
		game->ceiling_color= ft_strdup(pth);
	}
	return (free(color), SUCCESS);
}

int dup_check(int *arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		if(arr[i] > 1)
			return(printf("Duplicated identifier found\n"), FAIL);
		i++;
	}
	return SUCCESS;
}

void identifiers_end(char **splitted, int *grid_flag)
{
	if(splitted[0][0] == '1' || splitted[0][0] == '0' || splitted[0][0] == ' ')
		*grid_flag = 1;
}

int identifiers2(char **splitted, int *arr, t_game *game, int *grid_flag)
{
	if (dup_check(&arr) == FAIL)
		cleanup(*game);
	if (ft_strncmp(splitted[0], "NO", 2))
	{
		arr[0]++;
		game->no_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "SO", 2))
	{
		arr[1]++;
		game->so_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "EA", 2))
	{
		arr[2]++;
		game->ea_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "WE", 2))
	{
		arr[3]++;
		game->we_path = ft_strdup(splitted[1]);
	}
	else if (splitted[0] == 'F' || splitted[0] == 'C')
		color_check(&splitted[0], &splitted[1], &arr, &game);
	identifiers_end(splitted, &grid_flag);
}

int identifiers(char *line, int *arr, t_game *game, int *grid_flag)
{
	char **splitted;
	char *id;
	char *pth;

	if(line[0] != 'N' || line[0] != 'S' || line[0] != 'E' || line[0] != 'W' || 
		line[0] != 'C' || line[0] != 'F' || line[0] != '\n')
		return FAIL;
	splitted = ft_split(line, ' ');
	id = splitted[0];
	pth = splitted[1];
	if (identifiers2(&splitted, &arr, &game, &grid_flag) == FAIL)
		return (free(splitted), FAIL);
}

int check_first_line(char *line, int *arr, t_game *game)
{
	if(!line)
		return(FAIL);
	if(line[0] == '\n')
		return SUCCESS;
	if (identifiers(line, arr, &game, 0) == FAIL)
		return(FAIL);
}

int identifiers_grid(int fd, t_game *game, int *player)
{
	char *line;
	int i;
	int grid_flag;
	int *flags[6] = {0,0,0,0,0,0};

	line = get_next_line(fd);
	if (check_first_line(line, &flags, &game) == FAIL)
		return (printf("Identifiers has a problem\n"), FAIL);
	grid_flag = 0;
	i = 0;
	while(line = get_next_line(fd))
	{
		if(grid_flag)
		{
			grid(&game, line, &i);
			i++;
		}
		else if (identifiers(line, flags, &game, &grid_flag) == FAIL)
			return(FAIL);
	}
	return SUCCESS;
}

int files_parse(char *str, t_game *game)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		close(fd);
		return (printf("Error : Could not open file\n"), FAIL);
	}
	if(identifiers_grid(&game, str, 0) == FAIL)
	{
		close(fd);
		cleanup(game->grid);
		return FAIL;
	}
}
