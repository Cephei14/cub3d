/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/13 12:30:09 by rdhaibi          ###   ########.fr       */
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

unsigned int	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel_addr;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); // Return black if out of bounds
	pixel_addr = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel_addr);
}

int ray_casting(t_game *game)
{
	int		x;
	int		y;
	t_texture *texture; // <-- NEW: To store the chosen texture

	// --- 1. DRAW FLOOR AND CEILING (Unchanged) ---
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(game, x, y, game->ceiling_color);
			else
				my_mlx_pixel_put(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}

	// --- 2. RAY-CASTING LOOP (With new texturing logic) ---
	x = 0;
	while (x < WIDTH)
	{
		// --- A. Setup Ray and Player Variables (Unchanged) ---
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = game->dir_x + game->x_plane * cameraX;
		double rayDirY = game->dir_y + game->y_plane * cameraX;
		int mapX = (int)game->pos_x;
		int mapY = (int)game->pos_y;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double sideDistX;
		double sideDistY;
		int stepX;
		int stepY;

		// --- B. Calculate Step and Initial sideDist (Unchanged) ---
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

		// --- C. DDA Loop (Unchanged) ---
		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// --- ADD THIS BOUNDS CHECK ---
			// Check if ray is outside the map's height (Y)
			if (mapY < 0 || mapY >= game->map_height)
			{
				hit = 1; // Stop the ray, treat "out of bounds" as a wall
			}
			// Check if ray is outside the map's width (X)
			else if (mapX < 0 || (size_t)mapX >= ft_strlen(game->grid[mapY]))
			{
				hit = 1; // Stop the ray, treat "out of bounds" as a wall
			}
			// --- END OF CHECK ---

			// Now it's safe to check the grid
			else if (game->grid[mapY][mapX] == '1')
			{
				hit = 1;
			}
		}

		// --- D. Calculate Wall Height (Unchanged) ---
		double perpWallDist;
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		// --- E. (NEW) TEXTURE CALCULATION BLOCK ---

		// 1. Find which texture to use
		if (side == 1) // N/S Wall
		{
			if (rayDirY < 0)
				texture = &game->north_tex; // Ray is pointing up (North)
			else
				texture = &game->south_tex; // Ray is pointing down (South)
		}
		else // E/W Wall
		{
			if (rayDirX < 0)
				texture = &game->west_tex; // Ray is pointing left (West)
			else
				texture = &game->east_tex; // Ray is pointing right (East)
		}

		// 2. Calculate 'wallX' (the exact 0.0 to 1.0 hit spot on the wall)
		double wallX;
		if (side == 0) // E/W wall
			wallX = game->pos_y + perpWallDist * rayDirY;
		else // N/S wall
			wallX = game->pos_x + perpWallDist * rayDirX;
		wallX -= floor(wallX); // Get just the decimal part

		// 3. Calculate 'texX' (the x-coordinate on the texture)
		int texX = (int)(wallX * (double)texture->width);
		
		// 4. (Correction) Flip the texture if we're looking South or East
		// This prevents a "mirrored" texture
		if (side == 0 && rayDirX > 0) // East wall
			texX = texture->width - texX - 1;
		if (side == 1 && rayDirY < 0) // North wall
			texX = texture->width - texX - 1;

		// 5. Calculate texture Y stepping
		double texStep = 1.0 * texture->height / lineHeight;
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * texStep;

		// 6. Draw the vertical slice with textured pixels
		y = drawStart;
		while (y < drawEnd)
		{
			int texY = (int)texPos; // Get the y-coordinate on the texture
			texPos += texStep;     // Move to the next texture pixel for the next screen pixel
			
			unsigned int color = get_pixel_color(texture, texX, texY);
			
			my_mlx_pixel_put(game, x, y, color);
			y++;
		}
		// --- END OF NEW BLOCK ---
		
		x++;
	}

	// --- 3. PUT IMAGE TO WINDOW (Unchanged) ---
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
	mlx_loop_hook(game.mlx_ptr, ray_casting, &game); //It registers ray_castingas the "main loop."
	mlx_loop(game.mlx_ptr); //infinite loop, it keep listening to event...
	return (SUCCESS);
}
