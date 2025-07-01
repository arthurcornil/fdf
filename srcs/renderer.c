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

t_point	voxel_to_pixel(t_voxel voxel, t_env *env)
{
	t_point	pixel;
	t_point	projected_pixel;

	pixel.x = (voxel.x * env->view.zoom * (env->win_width / 2) / env->map->width) + (env->win_width / 3);
	pixel.y = (voxel.y * env->view.zoom * (env->win_height / 2) / env->map->height) - (env->win_height / 3);
	projected_pixel.x = ((pixel.x - pixel.y) * cos(M_PI / 6)) + env->view.shift.x;
	projected_pixel.y = ((pixel.x + pixel.y) * sin(M_PI / 6) - (voxel.z * env->view.z_scale)) + env->view.shift.y;
	return (projected_pixel);
}

void	rotate_z(t_voxel *voxel, t_env *env)
{
	float	tmp_x;
	float	tmp_y;
	float	cx = env->map->width / 2.0f;
	float	cy = env->map->height / 2.0f;

	tmp_x = voxel->x - cx;
	tmp_y = voxel->y - cy;

	float angle = env->view.rotation.z;
	float rotated_x = tmp_x * cos(angle) - tmp_y * sin(angle);
	float rotated_y = tmp_x * sin(angle) + tmp_y * cos(angle);
	voxel->x = rotated_x + cx;
	voxel->y = rotated_y + cy;
}

void	set_img_background(int height, int width, t_img *img, int color)
{
	int	i = 0;
	int	total_pixels = height * width;
	int	*buffer = (int *)img->addr;

	while (i < total_pixels)
		buffer[i++] = color;
}

float get_percentage(int current, int min, int max)
{
	if (max == min)
		return 0.0f;
	return (float)(current - min) / (float)(max - min);
}

t_color	int_to_color(int color)
{
	t_color	broken_color;
	broken_color.red = (color >> 16) & 0xFF;
	broken_color.green = (color >> 8) & 0xFF;
	broken_color.blue = color & 0xFF;

	return (broken_color);
}

int	color_to_int(t_color color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue);
}

static t_color	get_color(int z, t_map *map, int start, int end)
{
	float	percentage;
	t_color	color_start;
	t_color	color_end;
	t_color	color;

	percentage = get_percentage(z, map->lowest, map->highest);
	color_start = int_to_color(start);
	color_end = int_to_color(end);
	color.red = color_start.red + ((color_end.red - color_start.red) * percentage);
	color.green = color_start.green + ((color_end.green - color_start.green) * percentage);
	color.blue = color_start.blue + ((color_end.blue - color_start.blue) * percentage);
	return (color);
}

void	draw_fdf(t_env *env)
{
	t_img			img;
	unsigned int	x;
	unsigned int	y;
	t_voxel			voxel;
	t_point			pixel;
	t_point			next_pixel;
	t_color   		color1;
	t_color			color2;

	img.ptr = mlx_new_image(env->mlx, env->win_width, env->win_height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	set_img_background(env->win_height, env->win_width, &img, BG_COLOR);
	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->width)
		{
			color1 = get_color(env->map->points[y][x], env->map, START_COLOR, END_COLOR);
			voxel = (t_voxel){ x, y, env->map->points[y][x] };
			rotate_z(&voxel, env);
			pixel = voxel_to_pixel(
				voxel,
				env
			);
			if (x < env->map->width - 1)
			{
				color2 = get_color(env->map->points[y][x + 1], env->map, START_COLOR, END_COLOR);
				voxel = (t_voxel) { x + 1, y, env->map->points[y][x + 1] };
				rotate_z(&voxel, env);
				next_pixel = voxel_to_pixel(voxel, env);
				draw_line(
					&img,
					pixel,
					next_pixel,
					color1,
					color2
				);
			}
			if (y < env->map->height - 1)
			{
				color2 = get_color(env->map->points[y + 1][x], env->map, START_COLOR, END_COLOR);
				voxel = (t_voxel) { x, y + 1, env->map->points[y + 1][x] };
				rotate_z(&voxel, env);
				next_pixel = voxel_to_pixel(voxel, env);
				draw_line(
					&img,
					pixel,
					next_pixel,
					color1,
					color2
				);
			}
			x ++;
		}
		y ++;
	}
	mlx_put_image_to_window(env->mlx, env->window, img.ptr, env->menu_width, 0);
	mlx_destroy_image(env->mlx, img.ptr);
}

void	render_menu(t_env *env)
{
	int		margin;
	t_img	img;

	img.ptr = mlx_new_image(env->mlx, env->menu_width, env->win_height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	set_img_background(env->win_height, env->win_height, &img, 0x00FFFFFF);
	mlx_put_image_to_window(env->mlx, env->window, img.ptr, 0, 0);
	mlx_destroy_image(env->mlx, img.ptr);
	margin = 50;
	mlx_string_put(env->mlx, env->window, 55, 10, 0x00050214, "Controls");
	mlx_string_put(env->mlx, env->window, 15, 10 + margin, 0x00050214, "z: zoom in");
	mlx_string_put(env->mlx, env->window, 15, 30 + margin, 0x00050214, "x: zoom out");
	mlx_string_put(env->mlx, env->window, 15, 50 + margin, 0x00050214, "r: rotate");
	mlx_string_put(env->mlx, env->window, 15, 70 + margin, 0x00050214, "1: - z scale");
	mlx_string_put(env->mlx, env->window, 15, 90 + margin, 0x00050214, "2: + z scale");
	mlx_string_put(env->mlx, env->window, 15, 110 + margin, 0x00050214, "arrows: translate");
}

void	put_window(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
	render_menu(env);
	draw_fdf(env);
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
	else if (key == 15)
		env->view.rotation.z += 0.025f;
	else if (key == 53)
		free_and_exit(env);
	
	put_window(env);
	return (0);
}

void	render(t_map *map)
{
	t_env				env;

	env.map = map;
	env.view.zoom = 1.0f;
	env.view.shift = (t_point){ 0, 0 };
	env.view.rotation = (t_voxel){ 0.0f, 0.0f, 0.0f };
	env.view.z_scale = 1.0f;
	env.win_height = WINDOW_HEIGHT;
	env.win_width = WINDOW_WIDTH;
	env.menu_width = 200;
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, env.win_width + env.menu_width, env.win_height, "FdF");
	put_window(&env);
	mlx_hook(env.window, 2, 1L << 0, handle_keypress, &env);
	mlx_hook(env.window, 17, 0, handle_keypress, &env);
	mlx_loop(env.mlx);
}
