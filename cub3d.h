/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:41 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/10/31 12:08:12 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct s_game
{
	//mlx's data
	void *mlx_ptr;
	void *win_ptr;
	//map's data
	char **data;
	char *no;
	char *so;
	char *ea;
	char *we;
	int floor_color;
	int ceiling_color;
	//screen image's data
	void *img_ptr;
	char *img_first_pixel;
	int bpp;
	int line_len;
	int endian;
	//player's data
	char start_dir;
	int start_x;
	int start_y;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double x_plane;
	double y_plane;
	
} t_game;

#endif
