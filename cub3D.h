/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:41 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/11/17 18:48:41 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define SUCCESS 0
# define FAIL -1
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define MOVE_SPEED 0.6
# define ROT_SPEED 0.2

typedef struct s_game		t_game;
typedef struct s_ray		t_ray;
typedef struct s_texture	t_texture;
void	txtr_init_ns(t_game *game);
void	txtr_init_ew(t_game *game);
void	struct_init(t_game *game);
void	cleanup(t_game *game);
void	free_split(char **str);
void	free_grid(t_game *game);
void	free_paths_and_textures(t_game *game);
void	free_mlx(t_game *game);
void	init_player(t_game *game);
void	draw_floor_ceiling(t_game *game);
void	init_ray_step_x(t_game *game, t_ray *ray);
void	init_ray_step_y(t_game *game, t_ray *ray);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_projection(t_ray *ray);
void	calculate_texture_coords(t_game *game, t_ray *ray);
void	draw_textured_slice(t_game *game, t_ray *ray, int x);
void	handle_move_ws(int keycode, t_game *game);
void	handle_move_ad(int keycode, t_game *game);
void	handle_rotate(int keycode, t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
int		parse_identifiers(char *line, int *arr, t_game *game, int *grid_flag);
int		arg_check(char *str);
int		cu(char c_char, char p_char, int pos, int j);
int		is_valid_char(char c, char *valid_chars);
int		is_valid_char(char c, char *valid_chars);
int		textures(t_game *game);
int		c_idf(int *arr);
int		skip_spaces_minus(int *i, char *line);
int		wall_check(t_game *game, int pos, int i, int player);
int		ray_casting(t_game *game);
int		parse_grid(t_game *game, char *line, int *i, int *player);
int		create_trgb(int r, int g, int b);
int		color_check(char *id, char *pth, int *arr, t_game *game);
int		dup_check(int *arr);
int		parse_identifiers_and_grid(int fd, t_game *game, int *player, int i);
int		parsing(char *str, t_game *game);
int		parse_identifiers2(char **splitted, int *arr, t_game *game);
int		s_wall_check(char *current, char *previous);
int		handle_keypress(int keycode, t_game *game);
int		handle_window_close(t_game *game);
int		is_all_digits(char *str);
int		ns_line_check(char *line);
int		long_line(char *c_line, int pos);
int		is_wall(t_game *game, double x, double y);
int		get_len(int *c_len, int *p_len, t_game *game, int *i);
int		handle_keypress(int keycode, t_game *game);
int		get_pixel_color(t_texture *texture, int x, int y);

typedef struct s_parse_state
{
	int	*ident_arr;
	int	*grid_flag;
	int	*i;
}	t_parse_state;

typedef struct s_texture
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		wall_x;
	double		tex_step;
	double		tex_pos;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
}	t_ray;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_pixel;
	char		**g;
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		start_dir;
	int			floor_color;
	int			ceiling_color;
	int			map_height;
	int			bpp;
	int			line_len;
	int			endian;
	int			start_x;
	int			start_y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		x_plane;
	double		y_plane;
	t_texture	n_tex;
	t_texture	s_tex;
	t_texture	e_tex;
	t_texture	w_tex;

}	t_game;

#endif