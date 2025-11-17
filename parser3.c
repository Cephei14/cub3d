/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:15:32 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(char *str, t_game *game)
{
	int	fd;
	int	player;

	player = 0;
	game->g = NULL;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (printf("Error : Could not open file\n"), FAIL);
	if (parse_identifiers_and_grid(fd, game, &player, 0) == FAIL)
	{
		close(fd);
		return (FAIL);
	}
	return (close(fd), SUCCESS);
}

int	cu(char c_char, char p_char, int pos, int j)
{
	if (j < pos)
	{
		if (c_char == '1')
			return (SUCCESS);
		else if (is_valid_char(c_char, "0NSEW"))
		{
			if (is_valid_char(p_char, " "))
				return (FAIL);
		}
		else if (c_char == ' ')
		{
			if (is_valid_char(p_char, "0NSEW"))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	compare_wall(t_game *g, int i)
{
	int	j;

	j = 0;
	while (g->g[i][j])
	{
		if (is_valid_char(g->g[i][j], " 0NSEW") && g->g[i - 1][j] != '1')
			return (FAIL);
		j++;
	}
	return (SUCCESS);
}

int	long_line(char *c_line, int pos)
{
	while (c_line[pos])
	{
		if (c_line[pos] != '1')
			return (FAIL);
		pos++;
	}
	return (SUCCESS);
}

int	skip_spaces_minus(int *i, char *line)
{
	while (line[*i] && line[*i] == ' ')
		(*i)--;
	if (line[*i] != '1')
		return (FAIL);
	return (SUCCESS);
}
