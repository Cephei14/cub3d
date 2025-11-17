/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:12:10 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:33:20 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_grid(t_game *game)
{
	int	i;

	if (!game->g)
		return ;
	i = 0;
	while (game->g[i])
	{
		free(game->g[i]);
		i++;
	}
	free(game->g);
	game->g = NULL;
}

void	free_paths_and_textures(t_game *game)
{
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->ea_path)
		free(game->ea_path);
	if (game->we_path)
		free(game->we_path);
	if (game->n_tex.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->n_tex.img_ptr);
	if (game->s_tex.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->s_tex.img_ptr);
	if (game->e_tex.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->e_tex.img_ptr);
	if (game->w_tex.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->w_tex.img_ptr);
}

void	free_mlx(t_game *game)
{
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
}
