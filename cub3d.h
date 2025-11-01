/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:41 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/01 23:39:58 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define SUCCESS 0
# define FAIL -1

void txtr_init_NS(t_game *game);
void txtr_init_EW(t_game *game);
void struct_init(t_game *game);
void cleanup(t_game *game);

typedef struct s_texture
{
    void    *img_ptr; //Image's ID
    char    *addr;    //Address of the first pixel
    int     width;    //Width of the texture
    int     height;   //Height of the texture
    int     bpp;      //Bits per pixel
    int     line_len; //Number of bytes in one horizontal row of the image
    int     endian;   //(RGB) Byte's order
}   t_texture;

typedef struct s_game
{
    //mlx's data
    void *mlx_ptr;    //Connection's ID between projects and computer's graphics
    void *win_ptr;    //Window's ID
    
    //map's data
    char **data;      //Map's grid (<.cub> file)
	int width;		  //Grid's width
	int height;		  //Grid's height
    char *no_path;    //File's path to textures .xpm
    char *so_path;    //File's path to textures .xpm
    char *ea_path;    //File's path to textures .xpm
    char *we_path;    //File's path to textures .xpm
    int floor_color;  //Color as a single integer
    int ceiling_color;//Color as a single integer

    //screen image's data
    void *img_ptr;    //Blank canvas's ID
    char *img_pixel;  //Address of the first pixel of your canvas
    int bpp;          //Canvas's property : bits per pixel
    int line_len;     //Canvas's property : line length
    int endian;       //Canvas's property : (RGB) Byte's order
    
    //player's data
    char start_dir;   //Start direction (N,S,E,W)
    int start_x;      //Grid coordinates X (X,Y)
    int start_y;      //Grid coordinates Y (X,Y)
    double pos_x;     //Player's current X position 
    double pos_y;     //Player's current Y position 
    double dir_x;     //Player's current X direction 
    double dir_y;     //Player's current Y direction
    double x_plane;   //Camera's X plane vector(for raycasting).
    double y_plane;   //Camera's Y plane vector(for raycasting).

    //textures's data
    t_texture north_tex;
    t_texture south_tex;
    t_texture east_tex;
    t_texture west_tex;

} t_game;

#endif