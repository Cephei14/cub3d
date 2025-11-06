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

int parse_grid(t_game *game, char *line, int *i, int *player)
{
	game->grid = ft_realloc(game->grid, (*i) + 1);
	game->grid[*i] = ft_strdup(line);
	if ((*i > 0))
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
	if((NS_wall_check
	(player, game, i)) == FAIL)
		return(FAIL);
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
