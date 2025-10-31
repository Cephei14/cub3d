/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/10/31 12:11:55 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_check(char **map)
{
	return 0;
}

int main(int ac, char **av)
{
	if(av != 2)
	{
		return 1;
	}
	if(map_check == 1)
	{
		return 1;
	}
	t_game game;
	
	if ((game.mlx_ptr = mlx_init()) == NULL)
	{
		return 1;
	}

	if((game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cube 3D")) == NULL)
	{
		return 1;
	}
	
}
