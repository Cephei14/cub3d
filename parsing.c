/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/06 15:28:50 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_identifiers2(char **splitted, int *arr, t_game *game, int *grid_flag)
{
	if (splitted[1] == NULL)
    	return (printf("Error\nMissing data for identifier %s\n", splitted[0]), FAIL);
	if (ft_strncmp(splitted[0], "NO", 3) == 0)
	{
		arr[0]++;
		if (arr[0] > 1)
			return (printf("Error\nDuplicate identifier 'NO'\n"), FAIL);
		game->no_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "SO", 3) == 0)
	{
		arr[1]++;
		if (arr[1] > 1)
			return (printf("Error\nDuplicate identifier 'SO'\n"), FAIL);
		game->so_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "EA", 3) == 0)
	{
		arr[2]++;
		if (arr[2] > 1)
			return (printf("Error\nDuplicate identifier 'EA'\n"), FAIL);
		game->ea_path = ft_strdup(splitted[1]);
	}
	else if (ft_strncmp(splitted[0], "WE", 3) == 0)
	{
		arr[3]++;
		if (arr[3] > 1)
			return (printf("Error\nDuplicate identifier 'WE'\n"), FAIL);
		game->we_path = ft_strdup(splitted[1]);
	}
	else if ((ft_strncmp(splitted[0], "F", 2) == 0 && ft_strlen(splitted[0]) == 1) ||
         (ft_strncmp(splitted[0], "C", 2) == 0 && ft_strlen(splitted[0]) == 1))
	{
		if (color_check(splitted[0], splitted[1], arr, game) == FAIL)
			return (FAIL);
	}
    return (identifiers_end(splitted, grid_flag), SUCCESS);
}

int parse_identifiers(char *line, int *arr, t_game *game, int *grid_flag)
{
	char **splitted;
	int i;

	if(line[0] == '\n')
		return (SUCCESS);
	splitted = ft_split(line, ' ');
	if(!splitted || !splitted[0])
		return (free_split(splitted), SUCCESS);
	i = 0;
	while (splitted[i])
		i++;
	if (i != 2)
		return (free_split(splitted), printf("Error\nInvalid identifier format\n"), FAIL);
    if (parse_identifiers2(splitted, arr, game, grid_flag) == FAIL)
        return (free_split(splitted), FAIL);
    free_split(splitted);
    return (SUCCESS);
}


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
			if(i >= ft_strlen(previous) || (previous[i] != ' ' && previous[i] != '1'))
				return(FAIL);
		}
		else
			return(FAIL);
		i++;
	}
	return(SUCCESS);
}

int NS_wall_check(int player, t_game *game, int i)
{
	if (player == 0)
		return (printf("No player\n"), FAIL);
	if (i > 1)
	{
		if ((S_wall_check(game->grid[i - 1], game->grid[i - 2]) == FAIL))
			return (printf("Map not surrounded by walls\n"), FAIL);
	}
	else if (i == 1)
	{
		if (N_wall_check(game->grid[0]) == FAIL)
			return (printf("Map not surrounded by walls\n"), FAIL);
	}
}

int	check_space(int i, char *line, char p)
{
	if (i == 0)
	{
		if (line[i + 1] != ' ' && line[i + 1] != '1')
			return (FAIL);
		if (p != ' ' && p != '1')
			return (FAIL);
	}
	else if (line[i + 1] == '\0')
	{
		if (line[i - 1] != ' ' && line[i - 1] != '1')
			return (FAIL);
		if (p != ' ' && p != '1')
			return (FAIL);
	}
	else if (line[i + 1] != ' ' && line[i + 1] != '1' &&
				p != ' ' && p != '1' &&
				line[i - 1] != ' ' && line[i - 1] != '1')
		return (FAIL);
	return (SUCCESS);
}

int dup_check(int *arr)
{
	int i;

	i = 0;
	while(i < 6)
	{
		if(arr[i] > 1)
			return(printf("Duplicated identifier found\n"), FAIL);
		i++;
	}
	return SUCCESS;
}

int	check_player_or_floor(int i, char *line, char p)
{
	if (i == 0 || line[i + 1] == '\0')
		return (FAIL);
	if (line[i + 1] != '0' && line[i + 1] != '1' &&
		p != '0' && p != '1' &&
		line[i - 1] != '0' && line[i - 1] != '1')
		return (FAIL);
	return (SUCCESS);
}

int	check_validity(t_game *game, int i, char *line, char p, int *player, int y)
{
	if (line[i] == ' ')
	{
		if (check_space(i, line, p) == FAIL)
			return (FAIL);
	}
	else if (line[i] == 'N' || line[i] == 'S' ||
				line[i] == 'E' || line[i] == 'W')
	{
		(*player)++;
		game->start_x = i;
		game->start_y = y;
		game->start_dir = line[i];
		line[i] = '0';
		if (check_player_or_floor(i, line, p) == FAIL)
			return (FAIL);
    }
	else if (line[i] == '0')
	{
		if (check_player_or_floor(i, line, p) == FAIL)
			return (FAIL);
	}
	else if (line[i] == '1')
		return (SUCCESS);
	else
		return (FAIL);
	return (SUCCESS);
}

int EW_wall_check(t_game *game, char *line, int *player, int previous_idx)
{
	int		i;
	char	p;
	int		y;

	i = 0;
	while(line[i])
	{
		if (previous_idx == -1)
		{
			p = '1';
			y = 0;
		}
		else
		{
			if (i >= ft_strlen(game->grid[previous_idx]))
			{
				if (line[i] != ' ' && line[i] != '1')
					return (printf("Invalid map data\n"), FAIL);
				i++;
				continue;
			}
			p = game->grid[previous_idx][i];
			y = previous_idx + 1;
		}
		if (check_validity(game, i, line, p, player, y) == FAIL)
			return (printf("Invalid map data\n"), FAIL);
		if ((*player) > 1)
			return (printf("Many players\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}

int parse_grid(t_game *game, char *line, int *i, int *player)
{
	game->grid = ft_realloc(game->grid, (*i) + 2);
	game->grid[*i] = ft_strdup(line);

	if ((*i >= 0))
	{
		if((EW_wall_check(game, line, player, (*i) - 1)) == FAIL)
			return (FAIL);
	}
	(*i)++;
	return (SUCCESS);
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

void identifiers_end(char **splitted, int *grid_flag)
{
	if(splitted[0][0] == '1' || splitted[0][0] == '0' || splitted[0][0] == ' ')
		*grid_flag = 1;
}

int parse_identifiers_and_grid(int fd, t_game *game, int *player, int i)
{
	char *line;
	int grid_flag;
	int ident_flags[6] = {0,0,0,0,0,0};

	grid_flag = 0;
	line = get_next_line(fd);
	if (!line)
		return (printf("Empty file\n"), FAIL);
	while(line)
	{
		if(grid_flag)
			parse_grid(game, line, &i, player);
		else
		{
			if (parse_identifiers(line, ident_flags, game, &grid_flag) == FAIL)
				return(free(line), FAIL);
			if (grid_flag)
				parse_grid(game, line, &i, player);
		}
		free(line);
		line = get_next_line(fd);
	}
	if((NS_wall_check(player, game, i)) == FAIL)
		return(FAIL);
	i = 0;
	while (i < 6)
	{
	    if (ident_flags[i] == 0)
	        return (printf("Error\nMissing identifier\n"), FAIL);
	    i++;
	}
	return (SUCCESS);
}

int parsing(char *str, t_game *game)
{
	int fd;
	int player;

	player = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (printf("Error : Could not open file\n"), FAIL);
	if(parse_identifiers_and_grid(fd, game, &player, 0) == FAIL)
	{
		close(fd);
		return (cleanup(game), FAIL);
	}
	return (close(fd), SUCCESS);
}
