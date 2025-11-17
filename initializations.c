/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:58:25 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:32:35 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	struct_init(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_pixel = NULL;
	game->img_ptr = NULL;
	game->g = NULL;
	game->no_path = NULL;
	game->so_path = NULL;
	game->ea_path = NULL;
	game->we_path = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->start_y = 0;
	game->start_x = 0;
	game->start_dir = 0;
	game->pos_x = 0.0;
	game->pos_y = 0.0;
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->x_plane = 0.0;
	game->y_plane = 0.0;
	txtr_init_ns(game);
	txtr_init_ew(game);
}

void	init_player_ns(t_game *game)
{
	if (game->start_dir == 'N')
	{
		game->dir_x = 0.0;
		game->dir_y = -1.0;
		game->x_plane = 0.66;
		game->y_plane = 0.0;
	}
	else
	{
		game->dir_x = 0.0;
		game->dir_y = 1.0;
		game->x_plane = -0.66;
		game->y_plane = 0.0;
	}
}

void	init_player_ew(t_game *game)
{
	if (game->start_dir == 'E')
	{
		game->dir_x = 1.0;
		game->dir_y = 0.0;
		game->x_plane = 0.0;
		game->y_plane = 0.66;
	}
	else
	{
		game->dir_x = -1.0;
		game->dir_y = 0.0;
		game->x_plane = 0.0;
		game->y_plane = -0.66;
	}
}

void	init_player(t_game *game)
{
	game->pos_x = game->start_x + 0.5;
	game->pos_y = game->start_y + 0.5;
	if (game->start_dir == 'N' || game->start_dir == 'S')
		init_player_ns(game);
	else if (game->start_dir == 'E' || game->start_dir == 'W')
		init_player_ew(game);
}
