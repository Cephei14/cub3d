/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/06 15:38:35 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	arg_check(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (printf("Error\nFile name is too short.\n"), FAIL);
	if (ft_strncmp(str + len - 4, ".cub", 4) == 0)
		return (SUCCESS);
	return (printf("Error\nOnly <.cub> files are supported.\n", FAIL));
}

int	textures(t_game *game)
{
	game->north_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->no_path, &game->north_tex.width, &game->north_tex.height);
	game->south_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->so_path, &game->south_tex.width, &game->south_tex.height);
	game->east_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->ea_path, &game->east_tex.width, &game->east_tex.height);
	game->west_tex.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			game->we_path, &game->west_tex.width, &game->west_tex.height);

	if (!game->north_tex.img_ptr || !game->south_tex.img_ptr
		|| !game->east_tex.img_ptr || !game->west_tex.img_ptr)
	{
		return (printf("Error\nFailed to load textures\n"), FAIL);
	}
	game->north_tex.addr = mlx_get_data_addr(game->north_tex.img_ptr,
		&game->north_tex.bpp, &game->north_tex.line_len, &game->north_tex.endian);
	game->south_tex.addr = mlx_get_data_addr(game->south_tex.img_ptr,
		&game->south_tex.bpp, &game->south_tex.line_len, &game->south_tex.endian);
	game->east_tex.addr = mlx_get_data_addr(game->east_tex.img_ptr,
		&game->east_tex.bpp, &game->east_tex.line_len, &game->east_tex.endian);
	game->west_tex.addr = mlx_get_data_addr(game->west_tex.img_ptr,
		&game->west_tex.bpp, &game->west_tex.line_len, &game->west_tex.endian);
	return (SUCCESS);
}

int	close_game(t_game *game)
{
	cleanup(game);
	exit(SUCCESS);
	return (SUCCESS);
}

int ray_casting(t_game *game)
{
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_game	game;
	
	if(ac != 2)
		return (printf("Use ./cub3d <map's path> only <*.cub> files are supported\n"), FAIL);
	if(arg_check(av[1]) == FAIL)
		return (FAIL);
	struct_init(&game);
	if (parsing(av[1], &game) == FAIL)
		return (cleanup(&game), FAIL);
	if ((game.mlx_ptr = mlx_init()) == NULL)//connects the computer's graphics with my code
			return (cleanup(&game), FAIL);
	if((game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cube 3D")) == NULL) //opens a new window and give a title
		return (cleanup(&game), FAIL);
	if ((game.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT)) == NULL) //creates a "canvas" to start drawing on it
		return (cleanup(&game), FAIL);
	if ((game.img_pixel = mlx_get_data_addr(game.img_ptr, 
		&game.bpp, &game.line_len, &game.endian)) == NULL) //It takes canvas's informations then it update them and returns a pointer of the first pixel of the image
		return (cleanup(&game), FAIL);
	if (textures(&game) == FAIL) //upload textures...
        return (cleanup(&game), FAIL);
	init_player(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 0, handle_window_close, &game);
	if (ray_casting(&game) == FAIL) //draw pixels
		return (cleanup(&game), FAIL);
	mlx_loop(game.mlx_ptr); //infinite loop, it keep listening to event...
	return (SUCCESS);
}
