/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:10:42 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/07 00:41:09 by arcornil         ###   ########.fr       */
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

# define WINDOW_HEIGHT 563
# define WINDOW_WIDTH 900
# define START_COLOR 0x0066FF
# define END_COLOR 0x00FFFF
# define BG_COLOR 0x050214

typedef struct s_map
{
	unsigned int	height;
	unsigned int	width;
	int				**points;
	int				lowest;
	int				highest;
}	t_map;

typedef struct	s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_point
{
	int x;
	int y;
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

typedef int (*t_cmp_ft)(int, int);

t_map	*parse_map(char *filename);
void	free_map(t_map *map, int exit_status);
void	render(t_map *map);
void	put_pixel(t_img *img, t_point pixel, int color);
void	draw_line(t_img *img, t_point a, t_point b, t_color color_a, t_color color_b);
float	get_percentage(int current, int min, int max);
int		color_to_int(t_color color);
int		free_and_exit(t_env *env);

#endif
