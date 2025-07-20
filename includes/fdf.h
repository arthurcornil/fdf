/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:10:42 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/20 10:27:59 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>

# define WINDOW_HEIGHT 844
# define WINDOW_WIDTH 1500
# define MENU_WIDTH 200
# define START_COLOR 0x0066FF
# define END_COLOR 0x00FFFF
# define BG_COLOR 0x050214
# define MENU_COLOR 0xffffff
# define TEXT_COLOR 0x050214

# ifdef __APPLE__

typedef enum e_keycode
{
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
	KEY_PLUS = 69,
	KEY_MINUS = 78,
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	KEY_0 = 29,
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_TAB = 48,
	KEY_RETURN = 36,
	KEY_DELETE = 51,
	KEY_SHIFT_L = 257,
	KEY_SHIFT_R = 258,
	KEY_CTRL = 256,
}	t_keycode;

# elif defined __linux__

typedef enum e_keycode
{
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_UP = 65362,
	KEY_PLUS = 65451,
	KEY_MINUS = 65453,
	KEY_A = 97,
	KEY_B = 98,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_H = 104,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_M = 109,
	KEY_N = 110,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_U = 117,
	KEY_V = 118,
	KEY_W = 119,
	KEY_X = 120,
	KEY_Y = 121,
	KEY_Z = 122,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_0 = 48,
	KEY_ESC = 65307,
	KEY_SPACE = 32,
	KEY_TAB = 65289,
	KEY_RETURN = 65293,
	KEY_DELETE = 65535,
	KEY_SHIFT_L = 65505,
	KEY_SHIFT_R = 65506,
	KEY_CTRL = 65507,
}	t_keycode;

# endif

typedef struct s_map
{
	unsigned int	height;
	unsigned int	width;
	int				**points;
	int				lowest;
	int				highest;
}	t_map;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_voxel
{
	float	x;
	float	y;
	float	z;
}	t_voxel;

typedef struct s_view
{
	float	zoom;
	t_point	shift;
	float	z_scale;
	t_voxel	rotation;
}	t_view;

typedef struct s_env
{
	void			*mlx;
	void			*window;
	int				win_height;
	int				win_width;
	int				menu_width;
	t_map			*map;
	t_view			view;
}	t_env;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_line
{
	t_color	color_a;
	t_color	color_b;
	t_point	pixel_a;
	t_point	pixel_b;
}	t_line;

typedef struct s_line_loop_params
{
	t_img	*img;
	t_line	*line;
	t_point	pixel;
	int		dx;
	int		direction;
	bool	is_steep;
}	t_line_loop_params;

typedef struct s_connect_next_point_params
{
	t_point	point;
	t_env	*env;
	t_color	color;
	t_point	pixel;
	t_img	*img;
}	t_connect_next_point_params;

typedef int	(*t_cmp_ft)(int, int);

t_map			*parse_map(char *filename);
void			free_map(t_map *map, int exit_status);
void			render(t_map *map);
void			put_pixel(t_img *img, t_point pixel, int color);
void			draw_line(t_img *img, t_line *line);
float			get_percentage(int current, int min, int max);
int				color_to_int(t_color color);
int				free_and_exit(t_env *env);
void			free_strs(char **strs);
bool			is_same_width(char **strs, unsigned int expected_width);
int				*get_nums(char	**strs, unsigned int width);
unsigned int	get_width(char **strs);
int				get_extreme_point(t_map *map, t_cmp_ft cmp, int init_val);
int				is_higher(int a, int b);
int				is_lower(int a, int b);
bool			is_same_width(char **strs, unsigned int expected_width);
void			fill_lines(t_map *map, int fd);
void			put_line_pixels_loop(t_line_loop_params *p);
t_color			get_color(int z, t_map *map, int start, int end);
t_line			get_line(t_color color_a, t_color color_b,
					t_point pixel_a, t_point pixel_b);
void			draw_fdf(t_env *env, t_img *img);

#endif
