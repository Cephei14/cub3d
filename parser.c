/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:27:41 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_first_line(t_game *game, char *line, int *player, int *i)
{
	if (ns_line_check(line) == FAIL)
		return (printf("Wall error in the line \n<%s>\n", line), FAIL);
	*player += wall_check(game, 0, *i, 0);
	return (SUCCESS);
}

int	handle_subsequent_line(t_game *game, char *line, int *player, int *i)
{
	int	players_found;
	int	pos;
	int	p_len;
	int	c_len;

	pos = get_len(&c_len, &p_len, game, i);
	if (line[0] == '\n')
		*player = -1;
	if ((*player) > 1)
		return (printf("Many players\n"), FAIL);
	players_found = wall_check(game, pos, *i, 0);
	if (players_found == -2)
		return (printf("Wall error in the line \n<%s>\n", game->g[*i]), FAIL);
	*player += players_found;
	if (c_len > p_len && long_line(line, pos) == FAIL)
		return (printf("Invalid line1 \n<%s>\n", line), FAIL);
	else if (c_len < p_len && long_line(game->g[(*i) - 1], pos) == FAIL)
		return (printf("Invalid line2\n<%s>\n", game->g[(*i) - 1]), FAIL);
	return (SUCCESS);
}

int	player_wall_check(t_game *game, char *line, int *player, int *i)
{
	if (*i == 0)
	{
		if (handle_first_line(game, line, player, i) == FAIL)
			return (FAIL);
	}
	else
	{
		if (handle_subsequent_line(game, line, player, i) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

char	**copy_grid(t_game *game, int *i, char *line)
{
	int		j;
	char	**new_grid;

	j = 0;
	new_grid = malloc(sizeof(char *) * ((*i) + 2));
	while (j < *i)
	{
		new_grid[j] = ft_strdup(game->g[j]);
		j++;
	}
	new_grid[j] = ft_strdup(line);
	new_grid[j + 1] = NULL;
	if (game->g)
		free_split(game->g);
	return (new_grid);
}

int	parse_grid(t_game *game, char *line, int *i, int *player)
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
	game->g = copy_grid(game, i, trimmed_line);
	if (!game->g)
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
	game->g[*i] = NULL;
	free(trimmed_line);
	return (SUCCESS);
}
