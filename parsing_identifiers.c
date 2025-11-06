/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:16:30 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/06 13:48:37 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_identifiers2(char **splitted, int *arr, t_game *game, int *grid_flag)
{
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
	else if (ft_strncmp(splitted[0], "F", 2) == 0 || ft_strncmp(splitted[0], "C", 2) == 0)
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
