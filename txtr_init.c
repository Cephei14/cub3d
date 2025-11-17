/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtr_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:58:25 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 15:35:08 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	txtr_init_ns(t_game *game)
{
	game->n_tex.img_ptr = NULL;
	game->n_tex.addr = NULL;
	game->n_tex.width = 0;
	game->n_tex.height = 0;
	game->n_tex.bpp = 0;
	game->n_tex.line_len = 0;
	game->n_tex.endian = 0;
	game->s_tex.img_ptr = NULL;
	game->s_tex.addr = NULL;
	game->s_tex.width = 0;
	game->s_tex.height = 0;
	game->s_tex.bpp = 0;
	game->s_tex.line_len = 0;
	game->s_tex.endian = 0;
}

void	txtr_init_ew(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "Cube 3D");
	game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->img_pixel = mlx_get_data_addr(game->img_ptr,
			&game->bpp, &game->line_len, &game->endian);
	game->e_tex.img_ptr = NULL;
	game->e_tex.addr = NULL;
	game->e_tex.width = 0;
	game->e_tex.height = 0;
	game->e_tex.bpp = 0;
	game->e_tex.line_len = 0;
	game->e_tex.endian = 0;
	game->w_tex.img_ptr = NULL;
	game->w_tex.addr = NULL;
	game->w_tex.width = 0;
	game->w_tex.height = 0;
	game->w_tex.bpp = 0;
	game->w_tex.line_len = 0;
	game->w_tex.endian = 0;
}
