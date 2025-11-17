/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:11:55 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	skip_spaces_plus(int *i, char *line)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] != '1')
		return (FAIL);
	return (SUCCESS);
}

int	check_left(char *line, int i)
{
	if (is_valid_char(line[i], "0NSEW"))
	{
		if (i == 0)
			return (FAIL);
		if (line[i - 1] == ' ')
			return (FAIL);
	}
	return (SUCCESS);
}

int	check_right(char *line, int i)
{
	if (is_valid_char(line[i], "0NSEW"))
	{
		if (line[i + 1] == ' ' || line[i + 1] == '\n' || line[i + 1] == '\0')
			return (FAIL);
	}
	return (SUCCESS);
}

int	wall_check(t_game *g, int pos, int i, int player)
{
	int	j;

	j = 0;
	if (g->g[i][j] == ' ' && skip_spaces_plus(&j, g->g[i]) == FAIL)
		return (-2);
	while (g->g[i][j] && g->g[i][j] != '\n')
	{
		if (!is_valid_char(g->g[i][j], " 01NSEW"))
			return (-2);
		if (i > 0 && j < pos && (cu(g->g[i][j], g->g[i - 1][j], pos, j) == -1))
			return (-2);
		if (is_valid_char(g->g[i][j], "NSEW"))
		{
			player++;
			g->start_x = j;
			g->start_y = i;
			g->start_dir = g->g[i][j];
		}
		if ((check_right(g->g[i], j) == -1) || (check_left(g->g[i], j) == -1))
			return (-2);
		j++;
	}
	if (g->g[i][j] == ' ' && skip_spaces_minus(&j, g->g[i]) == FAIL)
		return (-2);
	return (player);
}

int	get_len(int *c_len, int *p_len, t_game *game, int *i)
{
	int	pos;

	*p_len = 0;
	if (game->g && *i > 0)
		*p_len = ft_strlen(game->g[(*i) - 1]);
	*c_len = ft_strlen(game->g[*i]);
	while (*p_len > 0 && game->g[(*i) - 1][(*p_len) - 1] == ' ')
		(*p_len)--;
	while (*c_len > 0 && game->g[*i][(*c_len) - 1] == ' ')
		(*c_len)--;
	pos = *c_len;
	if (*c_len > *p_len)
		pos = *p_len;
	return (pos);
}
