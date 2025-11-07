/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/07 12:09:01 by rdhaibi          ###   ########.fr       */
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
	return (printf("Error\nOnly <.cub> files are supported.\n"), FAIL);
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

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	dst = game->img_pixel + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int ray_casting(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(game, x, y, game->ceiling_color);
			else // Bottom half of screen
				my_mlx_pixel_put(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < WIDTH)
	{
		// ... (Main logic will go here)
		x++;
	}

	// This pushes your completed drawing to the screen
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
	return (SUCCESS);
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
	if ((game.mlx_ptr = mlx_init()) == NULL) //connects the computer's graphics with my code
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
	printf("NO %s\n", game.no_path);
	printf("SO %s\n", game.so_path);
	printf("EA %s\n", game.ea_path);
	printf("WE %s\n", game.we_path);
	printf("F %d\n", game.floor_color);
	printf("C %d\n", game.ceiling_color);
	for(int i = 0; game.grid[i]; i++)
		printf("%s", game.grid[i]);
	printf("\n\nstart_d = %c\n", game.start_dir);
	printf("start_x = %d\n", game.start_x);
	printf("start_y = %d\n", game.start_y);
	printf("pos_x = %f\n", game.pos_x);
	printf("pos_y = %f\n", game.pos_y);
	printf("dir_x = %f\n", game.dir_x);
	printf("dir_y = %f\n", game.dir_y);
	init_player(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game); //handle key hooks
	mlx_hook(game.win_ptr, 17, (1L << 17), handle_window_close, &game); //for X button
	mlx_loop_hook(game.mlx_ptr, ray_casting, &game); 
	mlx_loop(game.mlx_ptr); //infinite loop, it keep listening to event...
	return (SUCCESS);
}
