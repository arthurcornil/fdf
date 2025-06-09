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

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920
# define WINDOW_PADDING 20

typedef struct s_map
{
	unsigned int	height;
	unsigned int	width;
	int				**points;
}	t_map;

typedef struct	s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_env
{
	void			*mlx;
	void			*window;
	unsigned int	win_height;
	unsigned int	win_width;
	float			zoom;
	t_map			*map;
}	t_env;

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

t_map	*parse_map(char *filename);
void	free_map(t_map *map, int exit_status);
void	render(t_map *map);
void	put_pixel(t_img *img, t_point pixel, int color);
void	draw_line(t_point origin, t_point dest, t_img *img);

#endif
