/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:12:10 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/01 23:22:11 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cleanup(t_game *game)
{
	free_data(&game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr); //destroys the window
	exit(0);
}
