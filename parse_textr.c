/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 16:05:40 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_and_parse_rgb(char **colors, int *rgb)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (i >= 3)
			return (printf("Error\nInvalid color format\n"), FAIL);
		if (is_all_digits(colors[i]) == 0)
			return (printf("Error\nInvalid character\
				in color: %s\n", colors[i]),
				FAIL);
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (printf("Error\nColor out of range [0,255]\n"), FAIL);
		i++;
	}
	if (i != 3)
		return (printf("Error\nInvalid color format (must be R,G,B)\n"), FAIL);
	return (SUCCESS);
}

int	color_check(char *id, char *pth, int *arr, t_game *game)
{
	char	**colors;
	int		rgb[3];

	colors = ft_split(pth, ',');
	if (!colors)
		return (printf("Error\nMalloc failed in color_check\n"), FAIL);
	if (validate_and_parse_rgb(colors, rgb) == FAIL)
	{
		free_split(colors);
		return (FAIL);
	}
	free_split(colors);
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

int	handle_texture_ns(char **splitted, int *arr, t_game *game)
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
	else
		return (FAIL);
	return (SUCCESS);
}

int	handle_texture_ew(char **splitted, int *arr, t_game *game)
{
	if (ft_strncmp(splitted[0], "EA", 3) == 0)
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
	else
		return (FAIL);
	return (SUCCESS);
}

int	parse_identifiers2(char **splitted, int *arr, t_game *game)
{
	if (splitted[1] == NULL)
		return (printf("Error\nMissing data for\
			identifier %s\n", splitted[0]), FAIL);
	if (handle_texture_ns(splitted, arr, game) == SUCCESS)
		return (SUCCESS);
	if (handle_texture_ew(splitted, arr, game) == SUCCESS)
		return (SUCCESS);
	if ((ft_strncmp(splitted[0], "F", 2) == 0 && ft_strlen(splitted[0]) == 1)
		|| (ft_strncmp(splitted[0], "C", 2) == 0
			&& ft_strlen(splitted[0]) == 1))
	{
		if (color_check(splitted[0], splitted[1], arr, game) == FAIL)
			return (FAIL);
	}
	else
		return (printf("Error\nInvalid identifier format\n"), FAIL);
	return (SUCCESS);
}
