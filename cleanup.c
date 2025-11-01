/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:12:10 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/02 00:09:05 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_data(t_game *game)
{
	int	i;

	if (!game->data)
		return ;
	i = 0;
	while (game->data[i])
	{
		free(game->data[i]);
		i++;
	}
	free(game->data);
	game->data = NULL;
}

void cleanup(t_game *game)
{
	free_data(&game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr); //destroys the window
	exit(0);
}
