/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/10/31 13:45:42 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_check(char *str)
{
	return 0;
}

int arg_check(char *str)
{
	return 0;
}

void struct_init(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_first_pixel = NULL;
	game->img_ptr = NULL;
	game->data = NULL;
	game->no = NULL;
	game->so = NULL;
	game->ea = NULL;
	game->we = NULL;
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
}

int main(int ac, char **av)
{
	t_game game;
	
	if(av != 2)
	{
		ft_printf("Use ./cub3d <map's path>\n");
		return 1;
	}
	if(arg_check(av[1]) == 1 || map_check(av[1]) == 1)
		return 1;
	struct_init(&game);
	if ((game.mlx_ptr = mlx_init()) == NULL)
		return 1;
	if((game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cube 3D")) == NULL)
		return 1;
	if ((game.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT)) == NULL)
		return 1;
	


	
	mlx_destroy_window(game.mlx_ptr, game.win_ptr);
}
