/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:16:30 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/06 12:56:38 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_identifiers2(char **splitted, int *arr, t_game *game, int *grid_flag)
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

int parse_identifiers(char *line, int *arr, t_game *game, int *grid_flag)
{
	char **splitted;
	char *id;
	char *pth;

	if(line[0] == '\n')
		return (SUCCESS);
	splitted = ft_split(line, ' ');
	if(!splitted || !splitted[0])
		return (free_split(splitted), SUCCESS);
if (ft_strncmp(splitted[0], "F", 2) == 0 || ft_strncmp(splitted[0], "C", 2) == 0)
    {
        if (!splitted[1])
            return (printf("Error\nMissing color info\n"), FAIL);
    }
    else if (ft_strncmp(splitted[0], "NO", 3) == 0 || ft_strncmp(splitted[0], "SO", 3) == 0 ||
		ft_strncmp(splitted[0], "EA", 3) == 0 || ft_strncmp(splitted[0], "WE", 3) == 0)
    {
        if (!splitted[1])
            return (printf("Error\nMissing texture path\n"), FAIL);
    }
    if (identifiers2(splitted, arr, game, grid_flag) == FAIL)
        return (free_split(splitted), FAIL);
    free_split(splitted);
    return (SUCCESS);
}
