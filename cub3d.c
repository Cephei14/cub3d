/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/02 00:07:37 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int arg_check(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len < 4)
    {
        printf("Error\nFile name is too short.\n");
        return (FAIL);
    }
    if (ft_strncmp(str + len - 4, ".cub", 4) == 0)
        return (SUCCESS);
	printf("Error\nOnly <.cub> files are supported.\n");
    return (FAIL);
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

int main(int ac, char **av)
{
	t_game game;
	
	if(ac != 2)
	{
		printf("Use ./cub3d <map's path> only <*.cub> files are supported\n");
		return FAIL;
	}
	if(arg_check(av[1]) == FAIL)
		return FAIL;
		
	struct_init(&game);
	
	if (open_file_parse_(av[1], &game) == FAIL)
		cleanup(&game);

	if ((game.mlx_ptr = mlx_init()) == NULL) //connects the computer's graphics with my code
		cleanup(&game);
		
	if((game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cube 3D")) == NULL) //opens a new window and give a title
		cleanup(&game);
		
	if ((game.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT)) == NULL) //creates a "canvas" to start drawing on it
		cleanup(&game);
		
	if ((game.img_pixel = mlx_get_data_addr(game.img_ptr, 
		&game.bpp, &game.line_len, &game.endian)) == NULL) //It takes canvas's informations then it update them and returns a pointer of the first pixel of the image
		cleanup(&game);											//For the screen
		
	if (textures(&game) == FAIL) //upload textures...
		cleanup(&game);
		
	if (ray_casting(&game) == FAIL) //draw pixels
		cleanup(&game);
	
	mlx_loop(game.mlx_ptr); //infinite loop, it keep listening to event...
	
	exit_game(&game);
	
	return SUCCESS;
}
