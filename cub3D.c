/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 14:40:58 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	arg_check(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (printf("Error\nFile name is too short.\n"), FAIL);
	if (ft_strncmp(str + len - 4, ".cub", 4) == 0)
		return (SUCCESS);
	return (printf("Error\nOnly <.cub> files are supported.\n"), FAIL);
}

int	textures(t_game *game)
{
	game->n_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->no_path, &game->n_tex.width, &game->n_tex.height);
	game->s_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->so_path, &game->s_tex.width, &game->s_tex.height);
	game->e_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->ea_path, &game->e_tex.width, &game->e_tex.height);
	game->w_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->we_path, &game->w_tex.width, &game->w_tex.height);
	if (!game->n_tex.img_ptr || !game->s_tex.img_ptr
		|| !game->e_tex.img_ptr || !game->w_tex.img_ptr)
	{
		return (printf("Error\nFailed to load textures\n"), FAIL);
	}
	game->n_tex.addr = mlx_get_data_addr(game->n_tex.img_ptr, &game->n_tex.bpp,
			&game->n_tex.line_len, &game->n_tex.endian);
	game->s_tex.addr = mlx_get_data_addr(game->s_tex.img_ptr,
			&game->s_tex.bpp, &game->s_tex.line_len, &game->s_tex.endian);
	game->e_tex.addr = mlx_get_data_addr(game->e_tex.img_ptr,
			&game->e_tex.bpp, &game->e_tex.line_len, &game->e_tex.endian);
	game->w_tex.addr = mlx_get_data_addr(game->w_tex.img_ptr,
			&game->w_tex.bpp, &game->w_tex.line_len, &game->w_tex.endian);
	return (SUCCESS);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img_pixel + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel_addr;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel_addr = texture->addr
		+ (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel_addr);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Use ./cub3d <map's path> ... <*.cub>\n"), FAIL);
	if (arg_check(av[1]) == FAIL)
		return (FAIL);
	struct_init(&game);
	if (parsing(av[1], &game) == FAIL)
		return (cleanup(&game), FAIL);
	if (game.mlx_ptr == NULL)
		return (cleanup(&game), FAIL);
	if (game.win_ptr == NULL)
		return (cleanup(&game), FAIL);
	if (game.img_ptr == NULL)
		return (cleanup(&game), FAIL);
	if (game.img_pixel == NULL)
		return (cleanup(&game), FAIL);
	if (textures(&game) == FAIL)
		return (cleanup(&game), FAIL);
	init_player(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, (1L << 17), handle_window_close, &game);
	mlx_loop_hook(game.mlx_ptr, ray_casting, &game);
	return (mlx_loop(game.mlx_ptr), SUCCESS);
}
