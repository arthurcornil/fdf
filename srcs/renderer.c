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

t_point	voxel_to_pixel(t_voxel voxel, t_env *env)
{
	t_point	pixel;
	t_point	projected_pixel;

	pixel.x = voxel.x * env->view.zoom * (WINDOW_WIDTH / 2) / env->map->width + WINDOW_WIDTH / 2;
	pixel.y = voxel.y * env->view.zoom * (WINDOW_HEIGHT / 2) / env->map->height;
	projected_pixel.x = ((pixel.x - pixel.y) * cos(M_PI / 6)) + env->view.shift.x;
	projected_pixel.y = ((pixel.x + pixel.y) * sin(M_PI / 6) - (voxel.z * env->view.z_scale)) + env->view.shift.y;
	return (projected_pixel);
}

void	draw_fdf(t_env *env)
{
	t_img			img;
	unsigned int	x;
	unsigned int	y;
	t_point			pixel;
	t_point			next_pixel;
	int				color;

	img.ptr = mlx_new_image(env->mlx, env->win_width, env->win_height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->width)
		{
			color = 0x00FFFFFF;
			pixel = voxel_to_pixel(
				(t_voxel) { x, y, env->map->points[y][x] },
				env
			);
			if (env->map->points[y][x] > 0)
				color = 0x0000FF00;
			if (x < env->map->width - 1)
			{
				next_pixel = voxel_to_pixel((t_voxel) { x + 1, y, env->map->points[y][x + 1] }, env);
				draw_line(
					&img,
					pixel,
					next_pixel,
					color
				);
			}
			if (y < env->map->height - 1)
			{
				next_pixel = voxel_to_pixel((t_voxel) { x, y + 1, env->map->points[y + 1][x] }, env);
				draw_line(
					&img,
					pixel,
					next_pixel,
					color
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
	if (key == 6)
		env->view.zoom += 0.1f;
	else if (key == 7)
		env->view.zoom -= 0.1f;
	else if (key == 123)
		env->view.shift.x -= 10;
	else if (key == 124)
		env->view.shift.x += 10;
	else if (key == 125)
		env->view.shift.y += 10;
	else if (key == 126)
		env->view.shift.y -= 10;
	else if (key == 18)
		env->view.z_scale -= 1.0f;
	else if (key == 19)
		env->view.z_scale += 1.0f;
	
	printf("%d\n", key);

	mlx_clear_window(env->mlx, env->window);
	draw_fdf(env);
	return (0);
}


void	render(t_map *map)
{
	t_env				env;

	env.map = map;
	env.view.zoom = 1.0f;
	env.view.shift.x = 0;
	env.view.shift.y = 0;
	env.view.z_scale = 1.0f;
	env.win_height = WINDOW_HEIGHT;
	env.win_width = WINDOW_WIDTH;
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, env.win_width, env.win_height, "FdF");
	(void)map;
	draw_fdf(&env);
	mlx_key_hook(env.window, handle_keypress, &env);
	mlx_loop(env.mlx);
}
