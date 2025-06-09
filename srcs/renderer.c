/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:00:06 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/07 00:42:09 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

t_point	voxel_to_pixel(t_voxel voxel, t_map *map)
{
	t_point	pixel;
	t_point	projected_pixel;

	pixel.x = voxel.x * (WINDOW_WIDTH / 2) / map->width + WINDOW_WIDTH / 2;
	pixel.y = voxel.y * (WINDOW_HEIGHT / 2) / map->height;
	projected_pixel.x = (pixel.x - pixel.y) * cos(M_PI / 6);
	projected_pixel.y = (pixel.x + pixel.y) * sin(M_PI / 6) - voxel.z / 2;
	return (projected_pixel);
}

void	draw_fdf(t_env *env)
{
	t_img			img;
	unsigned int	x;
	unsigned int	y;
	t_point			pixel;
	t_point			next_pixel;

	img.ptr = mlx_new_image(env->mlx, env->win_width, env->win_height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->width)
		{
			pixel = voxel_to_pixel(
				(t_voxel) { x, y, env->map->points[y][x] },
				env->map
			);
			if (x < env->map->width - 1)
			{
				next_pixel = voxel_to_pixel((t_voxel) { x + 1, y, env->map->points[y][x + 1] }, env->map);
				draw_line(
					pixel,
					next_pixel,
					&img
				);
			}
			if (y < env->map->height - 1)
			{
				next_pixel = voxel_to_pixel((t_voxel) { x, y + 1, env->map->points[y + 1][x] }, env->map);
				draw_line(
					pixel,
					next_pixel,
					&img
				);
			}
			x ++;
		}
		y ++;
	}
	mlx_put_image_to_window(env->mlx, env->window, img.ptr, 0, 0);
}

int	handle_keypress(int key, t_env *env)
{
	if (key == 126)
		env->zoom += 0.1f;
	else if (key == 125)
		env->zoom -= 0.1f;
	mlx_clear_window(env->mlx, env->window);
	draw_fdf(env);
	return (0);
}


void	render(t_map *map)
{
	t_env				env;

	env.map = map;
	env.zoom = 1.0f;
	env.win_height = WINDOW_HEIGHT;
	env.win_width = WINDOW_WIDTH;
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, env.win_width, env.win_height, "FdF");
	(void)map;
	draw_fdf(&env);
	mlx_key_hook(env.window, handle_keypress, &env);
	mlx_loop(env.mlx);
}
