/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/07 13:35:21 by rdhaibi          ###   ########.fr       */
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
	int		x;
	int		y;

	// --- 1. DRAW FLOOR AND CEILING (Your existing code) ---
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2) // Top half of screen
				my_mlx_pixel_put(game, x, y, game->ceiling_color);
			else // Bottom half of screen
				my_mlx_pixel_put(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
	
	// --- 2. RAY-CASTING LOOP (The new part) ---
	x = 0;
	while (x < WIDTH)
	{
		// --- A. Setup Ray and Player Variables ---
		// (All of these are 'double' for precision)
		double cameraX = 2 * x / (double)WIDTH - 1; // x-coord on camera plane (-1 to 1)
		double rayDirX = game->dir_x + game->x_plane * cameraX;
		double rayDirY = game->dir_y + game->y_plane * cameraX;
		
		// Player's current grid square (int)
		int mapX = (int)game->pos_x;
		int mapY = (int)game->pos_y;

		// Distance from one grid line to the next (X or Y)
		// (Avoid division by zero if rayDir is 0)
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		// Distance from player to the *first* grid line
		double sideDistX;
		double sideDistY;

		// Which direction to step in the grid? (+1 or -1)
		int stepX;
		int stepY;

		// --- B. Calculate Step and Initial sideDist ---
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->pos_y) * deltaDistY;
		}

		// --- C. DDA (Digital Differential Analysis) Loop ---
		int hit = 0;  // Was a wall hit?
		int side; // Was it a N/S (1) or E/W (0) wall?

		while (hit == 0)
		{
			// "Step" the ray to the next grid square
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0; // Hit an East/West wall
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1; // Hit a North/South wall
			}
			// Check if the ray has hit a wall
			if (game->grid[mapY][mapX] == '1')
				hit = 1;
		}

		// --- D. Calculate Wall Height ---
		double perpWallDist;
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(HEIGHT / perpWallDist);

		// Find the Y start/end for drawing this slice
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		// --- E. Draw the Wall Slice ---
		int color;
		if (side == 1) // N/S wall
			color = 0x00FF0000; // Red
		else // E/W wall
			color = 0x0000FF00; // Green (different color for contrast)
		
		y = drawStart;
		while (y < drawEnd)
		{
			my_mlx_pixel_put(game, x, y, color);
			y++;
		}
		
		x++; // Move to the next vertical stripe
	}

	// --- 3. PUT IMAGE TO WINDOW (Your existing code) ---
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
	init_player(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game); //handle key hooks
	mlx_hook(game.win_ptr, 17, (1L << 17), handle_window_close, &game); //for X button
	mlx_loop_hook(game.mlx_ptr, ray_casting, &game); 
	mlx_loop(game.mlx_ptr); //infinite loop, it keep listening to event...
	return (SUCCESS);
}
