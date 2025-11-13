/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:35:33 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/13 11:47:32 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int mapX;
	int mapY;

	mapX = (int)x;
	mapY = (int)y;

	if (mapY < 0 || mapY >= game->map_height)
		return (1);

	// Check if player is outside the map's width (X)
	if (mapX < 0 || (size_t)mapX >= ft_strlen(game->grid[mapY]))
		return (1); // Treat "out of bounds" as a wall

	// Now it's safe to check the grid
	if (game->grid[mapY][mapX] == '1')
		return (1);
		
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	double new_x;
	double new_y;
	double old_dir_x;
	double	old_plane_x;
	
	if (keycode == KEY_ESC)
		handle_window_close(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
	{
		new_x = game->pos_x + game->dir_x * MOVE_SPEED;
		new_y = game->pos_y + game->dir_y * MOVE_SPEED;
		if (!is_wall(game, new_x, game->pos_y))
			game->pos_x = new_x;
		if (!is_wall(game, game->pos_x, new_y))
			game->pos_y = new_y;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		new_x = game->pos_x - game->dir_x * MOVE_SPEED;
		new_y = game->pos_y - game->dir_y * MOVE_SPEED;
		if (!is_wall(game, new_x, game->pos_y))
			game->pos_x = new_x;
		if (!is_wall(game, game->pos_x, new_y))
			game->pos_y = new_y;
	}
	else if (keycode == KEY_A)
	{
		new_x = game->pos_x - game->x_plane * MOVE_SPEED;
		new_y = game->pos_y - game->y_plane * MOVE_SPEED;
		if (!is_wall(game, new_x, game->pos_y))
			game->pos_x = new_x;
		if (!is_wall(game, game->pos_x, new_y))
			game->pos_y = new_y;
	}
	else if (keycode == KEY_D)
	{
		new_x = game->pos_x + game->x_plane * MOVE_SPEED;
		new_y = game->pos_y + game->y_plane * MOVE_SPEED;
		if (!is_wall(game, new_x, game->pos_y))
			game->pos_x = new_x;
		if (!is_wall(game, game->pos_x, new_y))
			game->pos_y = new_y;
	}
	else if (keycode == KEY_LEFT)
	{
		old_dir_x = game->dir_x;
		old_plane_x = game->x_plane;
		game->dir_x = game->dir_x * cos(-ROT_SPEED) - game->dir_y * sin(-ROT_SPEED);
		game->dir_y = old_dir_x * sin(-ROT_SPEED) + game->dir_y * cos(-ROT_SPEED);
		
		game->x_plane = game->x_plane * cos(-ROT_SPEED) - game->y_plane * sin(-ROT_SPEED);
		game->y_plane = old_plane_x * sin(-ROT_SPEED) + game->y_plane * cos(-ROT_SPEED);

	}
	else if (keycode == KEY_RIGHT)
	{
		old_dir_x = game->dir_x;
		old_plane_x = game->x_plane;
		
		// We use a positive ROT_SPEED for counter-clockwise
		game->dir_x = game->dir_x * cos(ROT_SPEED) - game->dir_y * sin(ROT_SPEED);
		game->dir_y = old_dir_x * sin(ROT_SPEED) + game->dir_y * cos(ROT_SPEED);
		
		game->x_plane = game->x_plane * cos(ROT_SPEED) - game->y_plane * sin(ROT_SPEED);
		game->y_plane = old_plane_x * sin(ROT_SPEED) + game->y_plane * cos(ROT_SPEED);
	}
	return (0);
}
