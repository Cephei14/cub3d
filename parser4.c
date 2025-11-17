/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:07:18 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:20:04 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	pswc(int player, t_game *game, int i)
{
	if (player == 0)
		return (printf("No player start position in map\n"), FAIL);
	if (player > 1)
		return (printf("More than one player in map\n"), FAIL);
	if (i < 3)
		return (printf("Map is too small\n"), FAIL);
	if (ns_line_check(game->g[i - 1]) == FAIL)
		return (printf("Last line not surrounded by walls\n"), FAIL);
	return (SUCCESS);
}

int	dup_check(int *arr)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (arr[i] > 1)
			return (printf("Duplicated identifier found\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}

int	create_trgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	process_line(char *line, t_game *game, int *player, t_parse_state *state)
{
	if (*player == -1)
	{
		if (line[0] != '\n')
			return (printf("new line inside map\n"), FAIL);
	}
	else if (*(state->grid_flag) == 1)
	{
		if (parse_grid(game, line, state->i, player) == FAIL)
			return (FAIL);
	}
	else
	{
		if (parse_identifiers(line, state->ident_arr, game, \
			state->grid_flag) == FAIL)
			return (FAIL);
		if (*(state->grid_flag) == 1)
		{
			if (parse_grid(game, line, state->i, player) == FAIL)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	parse_identifiers_and_grid(int fd, t_game *game, int *player, int i)
{
	char			*line;
	t_parse_state	state;
	int				grid_flag;
	int				ident_arr[6];

	ft_memset(ident_arr, 0, sizeof(int) * 6);
	grid_flag = 0;
	state.ident_arr = ident_arr;
	state.grid_flag = &grid_flag;
	state.i = &i;
	line = get_next_line(fd);
	if (!line)
		return (printf("Empty file\n"), FAIL);
	while (line)
	{
		if (process_line(line, game, player, &state) == FAIL)
			return (free(line), FAIL);
		free(line);
		line = get_next_line(fd);
	}
	if (((pswc(*player, game, i)) == FAIL) || (c_idf(ident_arr) == FAIL))
		return (FAIL);
	game->map_height = i;
	return (SUCCESS);
}
