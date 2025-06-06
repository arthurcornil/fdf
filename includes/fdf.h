/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:10:42 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 11:07:24 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>

# define WINDOW_HEIGHT 600
# define WINDOW_WIDTH 600
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
	t_img			img;
	unsigned int	win_height;
	unsigned int	win_width;
	unsigned int	padding;
}	t_env;

t_map	*parse_map(char *filename);
void	free_map(t_map *map, int exit_status);
void	draw_fdf(t_map *map);

#endif
