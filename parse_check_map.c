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

int N_wall_check(char *line)
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

int	S_wall_check(char *current, char *previous)
{
	int	i;

	i = 0;
	while(current[i])
	{
		if(current[i] == '1')
		{
			i++;
			continue;
		}
		else if(current[i] == ' ')	
		{
			if(previous[i] != ' ' && previous[i] != '1')
				return(FAIL);
		}
		else
			return(FAIL);
		i++;
	}
}

int	check_validity(int i, char *line, char p, int *player)
{
	if(line[i] == ' ')
	{
		if(line[i + 1] != ' ' && line[i + 1] != '1' && p != ' ' && p != '1' &&
			line[i - 1] != ' ' && line[i - 1] != '1')
			return(FAIL);
	}
	else if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' ||
		line[i] == 'W')
	{
		(*player)++;
		if(line[i + 1] != '0' && line[i + 1] != '1' && p != '0' && p != '1' &&
			line[i - 1] != '0' && line[i - 1] != '1')
			return(FAIL);
	}
	else if (line[i] == '0')
	{
		if(line[i + 1] != '0' && line[i + 1] != '1' && p != '0' && p != '1' &&
			line[i - 1] != '0' && line[i - 1] != '1')
			return(FAIL);
	}
	else if (line[i] == '1')
		return (SUCCESS);
	else
		return(FAIL);
}

int EW_wall_check(t_game *game, char *line, int *player, int previous_idx)
{
	int i;

	i = 0;
		return (printf("Invalid map\n"), FAIL);
	while(line[i])
	{
		if (check_validity(i, line, game->grid[previous_idx][i], &player) == FAIL)
			return (printf("Invalid map data\n"), FAIL);
		if ((*player) > 1)
			return (printf("Many players\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}

int grid(t_game *game, char *line, int *i)
{
	int player;

	ft_realloc(game->grid, (*i) + 1);
	game->grid[*i] = ft_strdup(line);
	if ((N_wall_check(game->grid[0])) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	if ((EW_wall_check(game, line, &player, (*i) - 1)) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
}

int	create_trgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

int color_check(char *id, char *pth, int *arr, t_game *game)
{
	char	**colors;
	int		rgb[3];
	int		i;

	colors = ft_split(pth, ',');
	if (!colors)
		return (printf("Error\nMalloc failed in color_check\n"), FAIL);
	i = 0;
	while (colors[i])
	{
		if (i >= 3)
		{
			free_split(colors);
			return (printf("Error\nInvalid color format\n"), FAIL);
		}
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_split(colors);
			return (printf("Error\nColor out of range [0,255]\n"), FAIL);
		}
		i++;
	}
	free_split(colors);
	if (i != 3)
		return (printf("Error\nInvalid color format (must be R,G,B)\n"), FAIL);
	if (id[0] == 'F')
	{
		arr[4]++;
		game->floor_color = create_trgb(rgb[0], rgb[1], rgb[2]);
	}
	else if (id[0] == 'C')
	{
		arr[5]++;
		game->ceiling_color = create_trgb(rgb[0], rgb[1], rgb[2]);
	}
	return (SUCCESS);
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
	if (dup_check(arr) == FAIL)
		return (printf("Duplicated identifier character found\n"), FAIL);
	if (ft_strncmp(splitted[0], "NO", 3) == 0)
	{
		arr[0]++;
		game->no_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "SO", 3) == 0)
	{
		arr[1]++;
		game->so_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "EA", 3) == 0)
	{
		arr[2]++;
		game->ea_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "WE", 3) == 0)
	{
		arr[3]++;
		game->we_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "F", 2) == 0 || ft_strncmp(splitted[0], "C", 2) == 0)
		color_check(splitted[0], splitted[1], arr, game); 
    return (identifiers_end(splitted, grid_flag), SUCCESS);
}

int identifiers(char *line, int *arr, t_game *game, int *grid_flag)
{
	char **splitted;
	char *id;
	char *pth;

	if(line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W' && 
		line[0] != 'C' && line[0] != 'F' && line[0] != '\n')
		return (printf("Invalid identifier character\n"), FAIL);
	splitted = ft_split(line, ' ');
	id = splitted[0];
	pth = splitted[1];
	if (identifiers2(splitted, arr, game, &grid_flag) == FAIL)
		return (free(splitted), FAIL);
}

int check_first_line(char *line, int *arr, t_game *game)
{
	if(!line)
		return (printf("Empty file\n"), FAIL);
	else if (identifiers(line, arr, game, 0) == FAIL)
		return (printf("Identifiers has a problem\n"), FAIL);
	return (SUCCESS);
}

int identifiers_and_grid(int fd, t_game *game)
{
	char *line;
	int i;
	int grid_flag;
	int flags[6] = {0,0,0,0,0,0};

	line = get_next_line(fd);
	if (check_first_line(line, flags, game) == FAIL)
		return (FAIL);
	grid_flag = 0;
	i = 0;
	while(line = get_next_line(fd))
	{
		if(grid_flag)
		{
			grid(&game, line, &i);
			i++;
		}
		else if (identifiers(line, flags, game, &grid_flag) == FAIL)
			return(FAIL);
	}
	if ((S_wall_check(game->grid[i]), game->grid[i - 1]) == FAIL)
		return (printf("Map not surrounded by walls\n"), FAIL);
	return (SUCCESS);
}

int files_parse(char *str, t_game *game)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		close(fd);
		return (printf("Error : Could not open file\n"), FAIL);
	}
	if(identifiers_and_grid(fd, game) == FAIL)
	{
		close(fd);
		cleanup(game);
		return FAIL;
	}
	close(fd);
	return (SUCCESS);
}
