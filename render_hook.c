/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:35:33 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:33:54 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(t_game *game, double x, double y)
{
	int	mapx;
	int	mapy;

	mapx = (int)x;
	mapy = (int)y;
	if (mapy < 0 || mapy >= game->map_height)
		return (1);
	if (mapx < 0 || (size_t)mapx >= ft_strlen(game->g[mapy]))
		return (1);
	if (game->g[mapy][mapx] == '1')
		return (1);
	return (0);
}

void	handle_move_ws(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;

	if (keycode == KEY_W || keycode == KEY_UP)
	{
		new_x = game->pos_x + game->dir_x * MOVE_SPEED;
		new_y = game->pos_y + game->dir_y * MOVE_SPEED;
	}
	else
	{
		new_x = game->pos_x - game->dir_x * MOVE_SPEED;
		new_y = game->pos_y - game->dir_y * MOVE_SPEED;
	}
	if (!is_wall(game, new_x, game->pos_y))
		game->pos_x = new_x;
	if (!is_wall(game, game->pos_x, new_y))
		game->pos_y = new_y;
}

void	handle_move_ad(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;

	if (keycode == KEY_A)
	{
		new_x = game->pos_x - game->x_plane * MOVE_SPEED;
		new_y = game->pos_y - game->y_plane * MOVE_SPEED;
	}
	else
	{
		new_x = game->pos_x + game->x_plane * MOVE_SPEED;
		new_y = game->pos_y + game->y_plane * MOVE_SPEED;
	}
	if (!is_wall(game, new_x, game->pos_y))
		game->pos_x = new_x;
	if (!is_wall(game, game->pos_x, new_y))
		game->pos_y = new_y;
}

void	handle_rotate(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	if (keycode == KEY_LEFT)
		rot_speed = -ROT_SPEED;
	else
		rot_speed = ROT_SPEED;
	old_dir_x = game->dir_x;
	old_plane_x = game->x_plane;
	game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
	game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
	game->x_plane = game->x_plane * cos(rot_speed)
		- game->y_plane * sin(rot_speed);
	game->y_plane = old_plane_x * sin(rot_speed)
		+ game->y_plane * cos(rot_speed);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_window_close(game);
	else if (keycode == KEY_W || keycode == KEY_UP || \
			keycode == KEY_S || keycode == KEY_DOWN)
		handle_move_ws(keycode, game);
	else if (keycode == KEY_A || keycode == KEY_D)
		handle_move_ad(keycode, game);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		handle_rotate(keycode, game);
	return (0);
}
