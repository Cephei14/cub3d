/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:41 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/06 15:59:30 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../cub3d2/libft/libft.h"
# include "../cub3d2/get_next_line/get_next_line.h"
# include "../cub3d2/minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define SUCCESS 0
# define FAIL -1
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

void txtr_init_NS(t_game *game);
void txtr_init_EW(t_game *game);
void struct_init(t_game *game);
int parse_identifiers(char *line, int *arr, t_game *game, int *grid_flag);
void cleanup(t_game *game);
int arg_check(char *str);
int textures(t_game *game);
int ray_casting(t_game *game);
void free_split(char **str);
void free_grid(t_game *game);
int parse_grid(t_game *game, char *line, int *i, int *player);
int create_trgb(int r, int g, int b);
int color_check(char *id, char *pth, int *arr, t_game *game);
int dup_check(int *arr);
void identifiers_end(char **splitted, int *grid_flag);
int parse_identifiers_and_grid(int fd, t_game *game, int *player, int i);
int parsing(char *str, t_game *game);
int parse_identifiers2(char **splitted, int *arr, t_game *game,
		int *grid_flag);
int N_wall_check(char *line);
int S_wall_check(char *current, char *previous);
int NS_wall_check(int player, t_game *game, int i);
int check_space(int i, char *line, char p);
int check_player_or_floor(int i, char *line, char p);
int check_validity(t_game *game, int i, char *line, char p, int *player, int y);
int EW_wall_check(t_game *game, char *line, int *player, int previous_idx);
void init_player(t_game *game);
int	handle_keypress(int keycode, t_game *game);
int	handle_window_close(t_game *game);

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
    char **grid;      //Map's grid (<.cub> file)
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