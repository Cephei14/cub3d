/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:34:52 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	c_idf(int *arr)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (arr[i] == 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	trim_and_split(char *line, char ***splitted)
{
	char	*trimmed_line;
	int		j;

	trimmed_line = ft_strtrim(line, " \n\t\v\f\r");
	if (!trimmed_line)
	{
		printf("Error\nTrim failed\n");
		return (-1);
	}
	*splitted = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!*splitted)
		return (-1);
	j = 0;
	while ((*splitted)[j])
		j++;
	return (j);
}

int	parse_identifiers(char *line, int *arr, t_game *game, int *grid_flag)
{
	char	**splitted;
	int		j;

	if (line[0] == '\n')
		return (SUCCESS);
	j = trim_and_split(line, &splitted);
	if (j == -1)
		return (FAIL);
	if (j == 0)
		return (free_split(splitted), SUCCESS);
	if (j > 2)
		return (free_split(splitted), printf("Invalid identifier\n"), FAIL);
	if ((line[0] == '1' || line[0] == '0' || line[0] == ' ')
		&& (c_idf(arr)) == SUCCESS)
	{
		*grid_flag = 1;
		return (free_split(splitted), SUCCESS);
	}
	if ((parse_identifiers2(splitted, arr, game)) == FAIL)
		return (free_split(splitted), FAIL);
	return (free_split(splitted), SUCCESS);
}

int	s_wall_check(char *current_line, char *previous_line)
{
	int	i;

	i = 0;
	while (current_line[i])
	{
		if (current_line[i] == '1')
		{
			i++;
			continue ;
		}
		else if (current_line[i] == ' ')
		{
			if (previous_line[i] != ' ' && previous_line[i] != '1')
				return (FAIL);
		}
		else
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	special_wall_check(char *current_line, char *next_line)
{
	int	i;

	i = 0;
	while (current_line[i])
	{
		if (is_valid_char(current_line[i], "0NSEW")
			&& (ft_strlen(next_line) < ft_strlen(current_line)))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
