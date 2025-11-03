/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:12:10 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/03 22:33:19 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_split(char **str)
{
	int i;

	if (!str)
        return;
	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void free_grid(t_game *game)
{
	int	i;

	if (!game->grid)
		return ;
	i = 0;
	while (game->grid[i])
	{
		free(game->grid[i]);
		i++;
	}
	free(game->grid);
	game->grid = NULL;
}

void cleanup(t_game *game)
{
	free_grid(game);
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->ea_path)
		free(game->ea_path);
	if (game->we_path)
		free(game->we_path);
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr) // This
		mlx_destroy_display(game->mlx_ptr); // and this are not guaranteed
	free(game->mlx_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}
