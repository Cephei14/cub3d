/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/14 17:32:20 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_char(char c, char *valid_chars)
{
	while (*valid_chars)
	{
		if (c == *valid_chars)
			return (1);
		valid_chars++;
	}
	return (0);
}

int parse_identifiers2(char **splitted, int *arr, t_game *game)
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
    return (SUCCESS);
}

int check_identifiers_nb(int *arr)
{
	int i;
	
	i = 0;
	while (i < 5)
	{
	    if (arr[i] == 0)
	        return (FAIL);
	    i++;
	}
	return(SUCCESS);
}

int parse_identifiers(char *line, int *arr, t_game *game, int *grid_flag)
{
	char **splitted;
	int i;
	int j;
	char *trimmed_line;

	if(line[0] == '\n')
		return (SUCCESS);
	trimmed_line = ft_strtrim(line, " \n\t\v\f\r");
	if (!trimmed_line)
		return (printf("Error\nTrim failed\n"), FAIL);
	splitted = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	j = 0;
	while(splitted[j])
		j++;
	printf("j = %d\n", j);
	if (j > 2)
		return (free_split(splitted), printf("Error\nInvalid identifier number\n"), FAIL);
	if(!splitted || !splitted[0])
		return (free_split(splitted), SUCCESS);
	if ((line[0] == '1' || line[0] == '0' || line[0] == ' ') &&
		(check_identifiers_nb(arr)) == SUCCESS)
	{
		*grid_flag = 1;
		return (free_split(splitted), SUCCESS);
	}
	i = 0;
	while (splitted[i])
		i++;
	if (i != 2 && *grid_flag)
		return (free_split(splitted), printf("Error\nInvalid identifier format\n"), FAIL);
    if ((parse_identifiers2(splitted, arr, game)) == FAIL)
		return (free_split(splitted), FAIL);
	return(free_split(splitted), SUCCESS);
}

int NS_wall_check(char *line)
{
	int	i;

	i = 0;
	while(line[i] && line[i] != '\n')
	{
		if(line[i] != ' ' && line[i] != '1')
			return (FAIL);
		i++;
	}
	return SUCCESS;
}

int	S_wall_check(char *current_line, char *previous_line)
{
	int	i;

	i = 0;
	while(current_line[i])
	{
		if(current_line[i] == '1')
		{
			i++;
			continue;
		}
		else if(current_line[i] == ' ')	
		{
			if(previous_line[i] != ' ' && previous_line[i] != '1')
				return (FAIL);
		}
		else
			return(FAIL);
		i++;
	}
	return(SUCCESS);
}

int	special_wall_check(char *current_line, char *next_line)
{
	int	i;

	i = 0;
	while(current_line[i])
	{
		if(is_valid_char(current_line[i], "0NSEW") && (ft_strlen(next_line) < ft_strlen(current_line)))
			return(FAIL);
		i++;
	}
	return(SUCCESS);
}

int player_S_wall_check(int player, t_game *game, int i)
{
	if (player == 0)
		return (printf("No player start position in map\n"), FAIL);
	if (player > 1)
		return (printf("More than one player in map\n"), FAIL);
	if (i < 3)
		return (printf("Map is too small\n"), FAIL);
	if (NS_wall_check(game->grid[i - 1]) == FAIL)
		return (printf("Last line not surrounded by walls\n"), FAIL);
	return (SUCCESS);
}

int	check_space(int i, char *line, char char_above)
{
	if(i != 0)
	{
		if (!is_valid_char(char_above, " 1") ||
			!is_valid_char(line[i - 1], " 1") ||
			!is_valid_char(line[i + 1], " 1"))
			return (FAIL);	
	}
	else
	{
		if (!is_valid_char(char_above, " 1") ||
			!is_valid_char(line[i + 1], " 1"))
			return (FAIL);	
	}
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

int	check_player_or_floor(int i, char *line, char char_above)
{
	if (i == 0 || line[i + 1] == '\0')
		return (FAIL);
	if (!is_valid_char(char_above, "01NSEW") || \
		!is_valid_char(line[i - 1], "01NSEW") || \
		!is_valid_char(line[i + 1], "01NSEW"))
		return (FAIL);
	return (SUCCESS);
}

int	check_validity(t_game *game, int i, char *line, char char_above, int *player, int current_line)
{
	if (line[i] == ' ')
	{
		if (check_space(i, line, char_above) == FAIL)
			return (FAIL);
	}
	else if (line[i] == 'N' || line[i] == 'S' ||
				line[i] == 'E' || line[i] == 'W')
	{
		(*player)++;
		game->start_x = i;
		game->start_y = current_line;
		game->start_dir = line[i];
		line[i] = '0';
		if (check_player_or_floor(i, line, char_above) == FAIL)
			return (FAIL);
    }
	else if (line[i] == '0')
	{
		if (check_player_or_floor(i, line, char_above) == FAIL)
			return (FAIL);
	}
	else if (line[i] == '1')
		return (SUCCESS);
	else
		return (FAIL);
	return (SUCCESS);
}

int EW_wall_check(t_game *game, char *line, int *player, int line_above)
{
	char	char_above;
	int		i;
	int		current_line;

	i = 0;
	if(line[0] == '\n')
		*player = -1;
	while(line[i] && line[i] != '\n')
	{
		if ((size_t)i >= ft_strlen(game->grid[line_above]))
		{
			if (line[i] != ' ' && line[i] != '1')
				return (printf("Invalid map data1\n"), FAIL);
			i++;
			continue;
		}
		current_line = line_above + 1;
		char_above = game->grid[line_above][i];
		if (check_validity(game, i, line, char_above, player, current_line) == FAIL)
			return (printf("Invalid map data2\n"), FAIL);
		if ((*player) > 1)
			return (printf("Many players\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}

int parse_grid(t_game *game, char *line, int *i, int *player)
{
	char	**new_grid;
	int		j;
	char	*trimmed_line;
	int		p_len;
	int		c_len;

	if ((*i) > 0 && line[0] == '\n')
	{
		*player = -1;
		return (SUCCESS);
	}
	p_len = 0;
	if (game->grid && *i > 0)
		p_len = ft_strlen(game->grid[(*i) - 1]);

	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (FAIL);

	c_len = ft_strlen(trimmed_line); // Get length *after* trimming

	new_grid = malloc(sizeof(char *) * ((*i) + 2));
	if (!new_grid)
		return (free(trimmed_line), FAIL);
	j = 0;
	if (game->grid)
	{
		while (j < *i)
		{
			new_grid[j] = ft_strdup(game->grid[j]);
			j++;
		}
	}
	new_grid[j] = ft_strdup(trimmed_line);
	if (game->grid)
		free_split(game->grid);
	game->grid = new_grid;

	if ((*i) == 0)
	{
		if (NS_wall_check(trimmed_line) == FAIL)
			return (free(trimmed_line), FAIL);
	}
	else if ((*i) > 0)
	{
		if((EW_wall_check(game, trimmed_line, player, (*i) - 1)) == FAIL)
			return (free(trimmed_line), FAIL);
		
		// This check is now safe to run
		if(p_len > c_len)
		{
			while (c_len < p_len) // Use c_len as the counter
			{
				// Added a check for ' ' (space)
				if (game->grid[(*i) - 1][c_len] != '1' && game->grid[(*i) - 1][c_len] != ' ')
					return (printf("Invalid map\n"), free(trimmed_line), FAIL);
				c_len++;
			}
		}
	}
	(*i)++;
	game->grid[*i] = NULL;
	free(trimmed_line);
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

int parse_identifiers_and_grid(int fd, t_game *game, int *player, int i)
{
	char *line;
	int grid_flag;
	int ident_arr[6] = {0,0,0,0,0,0};

	grid_flag = 0;
	line = get_next_line(fd);
	if (!line)
		return (printf("Empty file\n"), FAIL);
	while(line)
	{
		if(*player == -1)
		{
			while((line = get_next_line(fd)))
			{
				if(line && line[0] != '\n')
					return (printf("new line inside map\n"), FAIL);
			}
			break;
		}
		if(grid_flag)
		{
			if (parse_grid(game, line, &i, player) == FAIL)
				return(free(line), FAIL);
		}
		else
		{
			if (parse_identifiers(line, ident_arr, game, &grid_flag) == FAIL)
				return(free(line), FAIL);
			if(grid_flag)
			{
				if(parse_grid(game, line, &i, player) == FAIL)
					return(free(line), FAIL);
			}
		}
		if(line)
			free(line);
		line = get_next_line(fd);
	}
	if((player_S_wall_check(*player, game, i)) == FAIL)
		return(FAIL);
	if (check_identifiers_nb(ident_arr) == FAIL)
		return(printf("Missing identifier"), FAIL);
	game->map_height = i;
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
		return (FAIL);
	}
	return (close(fd), SUCCESS);
}
