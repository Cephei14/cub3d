/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/01 15:10:07 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_check(t_game *game, int n)
{
	int	i;
	int	j;

	i = 0;
	while (game->data[0][i] || game->data[n][i])
	{
		if (game->data[0][i] != '1' || game->data[n][i] != '1')
			return (ft_printf("Error\nMap is not enclosed by walls\n"), FAIL);
		i++;
	}
	i = 1;
	while(game->data[i] && i < n)
	{
		j = ft_strlen(game->data[i]);
		if (game->data[i][0] != '1' || game->data[i] != '1')
			return (ft_printf("Error\nMap is not enclosed by walls\n"), FAIL);
		i++;
	}
	return (SUCCESS);
}

int map_check(t_game *game, char *str)
{
	int n;
	
	while(game->data[n])
		n++;
	wall_check(str, n);
	return SUCCESS;
}

int arg_check(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len < 4)
    {
        ft_printf("Error\nFile name is too short.\n");
        return (FAIL);
    }
    
    if (ft_strncmp(str + len - 4, ".cub", 4) == 0)
        return (SUCCESS);

    ft_printf("Error\nOnly <.cub> files are supported.\n");
    return (FAIL);
}

void txtr_init_NS(t_game *game)
{
	game->north_tex.img_ptr = NULL;
	game->north_tex.addr = NULL;
	game->north_tex.width = 0;
	game->north_tex.height = 0;
	game->north_tex.bpp = 0;
	game->north_tex.line_len = 0;
	game->north_tex.endian = 0;
	
	game->south_tex.img_ptr = NULL;
	game->south_tex.addr = NULL;
	game->south_tex.width = 0;
	game->south_tex.height = 0;
	game->south_tex.bpp = 0;
	game->south_tex.line_len = 0;
	game->south_tex.endian = 0;
}
void txtr_init_EW(t_game *game)
{
	game->east_tex.img_ptr = NULL;
	game->east_tex.addr = NULL;
	game->east_tex.width = 0;
	game->east_tex.height = 0;
	game->east_tex.bpp = 0;
	game->east_tex.line_len = 0;
	game->east_tex.endian = 0;
	
	game->west_tex.img_ptr = NULL;
	game->west_tex.addr = NULL;
	game->west_tex.width = 0;
	game->west_tex.height = 0;
	game->west_tex.bpp = 0;
	game->west_tex.line_len = 0;
	game->west_tex.endian = 0;
	
}


void struct_init(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_pixel = NULL;
	game->img_ptr = NULL;
	game->data = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->start_y = 0;
	game->start_x = 0;
	game->start_dir = 0;
	game->pos_x = 0.0;
	game->pos_y = 0.0;
	game->dir_x = 0.0;
	game->dir_y = 0.0;
	game->x_plane = 0.0;
	game->y_plane = 0.0;
	txtr_init_NS(&game);
	txtr_init_EW(&game);
}

int exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr); //destroys the window
	exit(0);
}

int textures(t_game *game)
{
	int width;
	int height;
	
	mlx_xpm_file_to_image(game->mlx_ptr, "/wall/wall.xpm", width, height);
}

int ray_casting(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0); //Adjusts (0, 0) of canvas with (0, 0) with the image
}

void exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr); //destroys the window
	exit(0);
}

int main(int ac, char **av)
{
	t_game game;
	
	if(ac != 2)
	{
		ft_printf("Use ./cub3d <map's path>\n");
		return FAIL;
	}
	if(arg_check(av[1]) == 1 || map_check(&game, av[1]) == 1)
		return FAIL;
	struct_init(&game);
	if ((game.mlx_ptr = mlx_init()) == NULL) //connects the computer's graphics with my code
		return FAIL;
		
	if((game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cube 3D")) == NULL) //opens a new window and give a title
		return FAIL;
		
	if ((game.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT)) == NULL) //creates a "canvas" to start drawing on it
		return FAIL;
		
	if ((game.img_pixel = mlx_get_data_addr(game.img_ptr, 
		&game.bpp, &game.line_len, &game.endian)) == NULL) //you give it the canvas and other informations's adrresses so it fill those informations and return a pointer of the first pixel of the image
		return FAIL;											//this one is for the screen
		
	if (textures(&game) == 1) //upload textures...
		return FAIL;
		
	if (ray_casting(&game) == 1) //draw pixels
		return FAIL;
	
	mlx_loop(game.mlx_ptr); //infinite loop, it keep listening to event...
	exit_game(&game);
	return SUCCESS;
}
