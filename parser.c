/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/14 18:23:06 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int wall_check(t_game *game, int pos, int i, int player);

static int is_all_digits(char *str)
{
    int i = 0;
    
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int	ns_line_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

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
	else
        return (printf("Error\nInvalid identifier format\n"), FAIL);
    return (SUCCESS);
}

int check_identifiers_nb(int *arr)
{
	int i;
	
	i = 0;
	while (i < 6)
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

int	player_S_wall_check(int player, t_game *game, int i)
{
	if (player == 0)
		return (printf("No player start position in map\n"), FAIL);
	if (player > 1)
		return (printf("More than one player in map\n"), FAIL);
	if (i < 3)
		return (printf("Map is too small\n"), FAIL);
	if (ns_line_check(game->grid[i - 1]) == FAIL)
		return (printf("Last line not surrounded by walls\n"), FAIL);
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
			return (printf("Error\nInvalid color format\n"), free_split(colors), FAIL);
		if (is_all_digits(colors[i]) == 0)
            return (printf("Error\nInvalid character in color: %s\n", colors[i]), free_split(colors), FAIL);
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (printf("Error\nColor out of range [0,255]\n"), free_split(colors), FAIL);
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
			if(line[0] != '\n')
				return (free(line), printf("new line inside map\n"), FAIL);
		}
		else if(grid_flag)
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
	game->grid = NULL;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (printf("Error : Could not open file\n"), FAIL);
	if(parse_identifiers_and_grid(fd, game, &player, 0) == FAIL)
	{
		close(fd);
		return (FAIL);
	}
	return (close(fd), SUCCESS);
}

int check_up(char c_char, char p_char, int pos, int j)
{
	if (j < pos)
	{
		if (c_char == '1')
			return SUCCESS;
		else if (is_valid_char(c_char, "0NSEW"))
		{
			if(is_valid_char(p_char, " "))
				return FAIL;
		}
		else if (c_char == ' ')
		{
			if(is_valid_char(p_char, "0NSEW"))
				return FAIL;
		}
	}
	return SUCCESS;
}

int compare_wall(t_game *game, int i)
{
	int j;

	j = 0;
	while(game->grid[i][j])
	{
		if(is_valid_char(game->grid[i][j], " 0NSEW") && game->grid[i - 1][j] != '1')
			return FAIL;
		j++;
	}
	return SUCCESS;
}

int long_line(char *c_line, int pos)
{
	while(c_line[pos])
	{
		if(c_line[pos] != '1')
			return FAIL;
		pos++;
	}
	return SUCCESS;
}

int skip_spaces_minus(int *i, char *line)
{
	while(line[*i] && line[*i] == ' ')
		(*i)--;
	if (line[*i] != '1')
		return FAIL;
	return SUCCESS;
}

int skip_spaces_plus(int *i, char *line)
{
	while(line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] != '1')
		return FAIL;
	return SUCCESS;
}

int check_left(char *line, int i)
{
    if (is_valid_char(line[i], "0NSEW"))
    {
        if (i == 0) 
            return FAIL;
        if (line[i - 1] == ' ')
            return FAIL;
    }
    return SUCCESS;
}

int check_right(char *line, int i)
{
    if (is_valid_char(line[i], "0NSEW"))
    {
        if (line[i + 1] == ' ' || line[i + 1] == '\n' || line[i + 1] == '\0')
            return FAIL;
    }
    return SUCCESS;
}

int	wall_check(t_game *game, int pos, int i, int player)
{
	int	j;

	j = 0;
	if (game->grid[i][j] == ' ' && skip_spaces_plus(&j, game->grid[i]) == FAIL)
		return (-2);
	while (game->grid[i][j] && game->grid[i][j] != '\n')
    {
        if (!is_valid_char(game->grid[i][j], " 01NSEW"))
            return (-2);
		if (i > 0 && j < pos && (check_up(game->grid[i][j], game->grid[i - 1][j], pos, j) == FAIL))
		    return (-2);
		if (is_valid_char(game->grid[i][j], "NSEW"))
		{
			player++;
			game->start_x = j;
			game->start_y = i;
			game->start_dir = game->grid[i][j];
		}
		if((check_right(game->grid[i], j) == FAIL) || (check_left(game->grid[i], j) == FAIL))
			return (-2);
		j++;
	}
	if (game->grid[i][j] == ' ' && skip_spaces_minus(&j, game->grid[i]) == FAIL)
		return (-2);
	return (player);
}

int get_len(int *c_len, int *p_len, t_game *game, int *i)
{
    int pos;

    *p_len = 0;
    if (game->grid && *i > 0)
        *p_len = ft_strlen(game->grid[(*i) - 1]);
    *c_len = ft_strlen(game->grid[*i]);
    while(*p_len > 0 && game->grid[(*i) - 1][(*p_len) - 1] == ' ')
        (*p_len)--;
    while(*c_len > 0 && game->grid[*i][(*c_len) - 1] == ' ')
        (*c_len)--;
    pos = *c_len;
    if (*c_len > *p_len)
        pos = *p_len;
    return pos;
}

int player_wall_check(t_game *game, char *line, int *player, int *i)
{
	int players_found;
    int pos;
    int p_len;
    int c_len;

    c_len = 0;
    if (*i == 0)
    {
        pos = 0;
        if (ns_line_check(line) == FAIL)
            return (printf("Wall error in the line \n<%s>\n", line), FAIL);
        *player += wall_check(game, 0, *i, 0);
    }
    else
    {
        pos = get_len(&c_len, &p_len, game, i);
        if (line[0] == '\n')
            *player = -1;
		if ((*player) > 1)
			return (printf("Many players\n"), FAIL);
		players_found = wall_check(game, pos, *i, 0);
		if (players_found == -2)
			return (printf("Wall error in the line \n<%s>\n", game->grid[*i]), FAIL);
		*player += players_found;
		if (c_len > p_len && long_line(line, pos) == FAIL)
			return (printf("Invalid line1 \n<%s>\n", line), FAIL);
		else if (c_len < p_len && long_line(game->grid[(*i) - 1], pos) == FAIL)
			return (printf("Invalid line2\n<%s>\n", game->grid[(*i) - 1]), FAIL);
	}
	return (SUCCESS);
}

char **copy_grid(t_game *game, int *i, char *line)
{
	int j;
	char **new_grid;

	j = 0;
	new_grid = malloc(sizeof(char *) * ((*i) + 2));
	while (j < *i)
	{
		new_grid[j] = ft_strdup(game->grid[j]);
		j++;
	}
	new_grid[j] = ft_strdup(line);
	new_grid[j + 1] = NULL;
	if (game->grid)
		free_split(game->grid);
	return (new_grid);
}

int parse_grid(t_game *game, char *line, int *i, int *player)
{
	char	*trimmed_line;

	if (line[0] == '\n')
    {
        *player = -1;
        return (SUCCESS);
    }
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (FAIL);
	game->grid = copy_grid(game, i, trimmed_line);
	if (!game->grid)
	{
		free(trimmed_line);
		return (FAIL);
	}
	if (player_wall_check(game, trimmed_line, player, i) == FAIL)
	{
		free(trimmed_line);
		return (FAIL);
	}
	(*i)++;
	game->grid[*i] = NULL;
	free(trimmed_line);
	return (SUCCESS);
}
