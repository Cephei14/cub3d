/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:59:06 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/06 13:02:10 by rdhaibi          ###   ########.fr       */
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

int	check_validity(int i, char *line, char p, int *player)
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
	int i;

	i = 0;
	while(line[i])
	{
		if (i >= ft_strlen(game->grid[previous_idx]))
    	{
    	    if (line[i] != ' ' && line[i] != '1')
    	        return (printf("Invalid map data\n"), FAIL);
            i++;
            continue;
    	}
    	if (check_validity(i, line, game->grid[previous_idx][i], player) == FAIL)
			return (printf("Invalid map data\n"), FAIL);
		
		if ((*player) > 1)
			return (printf("Many players\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}
