/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:58:25 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/01 15:58:34 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void txtr_init_NS(t_game *game)
{
	game->north_tex.img_ptr = NULL;
	game->north_tex.addr = NULL;
	game->north_tex.width = 0;
	game->north_tex.height = 0;
	game->north_tex.bpp = 0;
	game->north_tex.line_len = 0;
	game->north_tex.endian = 0;
	
	game->south_tex.img_ptr = NULL;
	game->south_tex.addr = NULL;
	game->south_tex.width = 0;
	game->south_tex.height = 0;
	game->south_tex.bpp = 0;
	game->south_tex.line_len = 0;
	game->south_tex.endian = 0;
}
void txtr_init_EW(t_game *game)
{
	game->east_tex.img_ptr = NULL;
	game->east_tex.addr = NULL;
	game->east_tex.width = 0;
	game->east_tex.height = 0;
	game->east_tex.bpp = 0;
	game->east_tex.line_len = 0;
	game->east_tex.endian = 0;
	
	game->west_tex.img_ptr = NULL;
	game->west_tex.addr = NULL;
	game->west_tex.width = 0;
	game->west_tex.height = 0;
	game->west_tex.bpp = 0;
	game->west_tex.line_len = 0;
	game->west_tex.endian = 0;
	
}

void struct_init(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_pixel = NULL;
	game->img_ptr = NULL;
	game->data = NULL;
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
	txtr_init_NS(&game);
	txtr_init_EW(&game);
}
