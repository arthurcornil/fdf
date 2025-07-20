/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:00:06 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/20 10:21:28 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_background(t_point	dimensions, t_img *img, int color, int offset)
{
	int		x;
	int		y;
	char	*pixel;

	if (!img || !img->addr)
		return ;
	y = 0;
	while (y < dimensions.y)
	{
		x = 0;
		while (x < dimensions.x)
		{
			pixel = img->addr + y * img->line_length
				+ (x + offset) * (img->bits_per_pixel / 8);
			*(int *)pixel = color;
			x ++;
		}
		y ++;
	}
}

void	draw_menu(t_env *env)
{
	int		margin;

	margin = 50;
	mlx_string_put(env->mlx, env->window, 70, 20,
		TEXT_COLOR, "Controls");
	mlx_string_put(env->mlx, env->window, 15, 20 + margin,
		TEXT_COLOR, "i: zoom in");
	mlx_string_put(env->mlx, env->window, 15, 40 + margin,
		TEXT_COLOR, "o: zoom out");
	mlx_string_put(env->mlx, env->window, 15, 60 + margin,
		TEXT_COLOR, "z: rotate");
	mlx_string_put(env->mlx, env->window, 15, 80 + margin,
		TEXT_COLOR, "1: - z scale");
	mlx_string_put(env->mlx, env->window, 15, 100 + margin,
		TEXT_COLOR, "2: + z scale");
	mlx_string_put(env->mlx, env->window, 15, 120 + margin,
		TEXT_COLOR, "arrows: translate");
}

void	put_window(t_env *env)
{
	t_img	img;

	img.ptr = mlx_new_image(env->mlx, env->win_width, env->win_height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	set_background((t_point){env->menu_width, env->win_height},
		&img, MENU_COLOR, 0);
	set_background((t_point){env->win_width - env->menu_width, env->win_height},
		&img, BG_COLOR, env->menu_width);
	draw_fdf(env, &img);
	mlx_put_image_to_window(env->mlx, env->window, img.ptr, 0, 0);
	draw_menu(env);
	mlx_destroy_image(env->mlx, img.ptr);
}

int	handle_keypress(int key, t_env *env)
{
	if (key == KEY_I)
		env->view.zoom += 0.1f;
	else if (key == KEY_O)
		env->view.zoom -= 0.1f;
	else if (key == KEY_LEFT)
		env->view.shift.x -= 10;
	else if (key == KEY_RIGHT)
		env->view.shift.x += 10;
	else if (key == KEY_DOWN)
		env->view.shift.y += 10;
	else if (key == KEY_UP)
		env->view.shift.y -= 10;
	else if (key == KEY_1)
		env->view.z_scale -= 1.0f;
	else if (key == KEY_2)
		env->view.z_scale += 1.0f;
	else if (key == KEY_Z)
		env->view.rotation.z += 0.02f;
	else if (key == KEY_ESC)
		free_and_exit(env);
	put_window(env);
	return (0);
}

void	render(t_map *map)
{
	t_env				env;

	env.map = map;
	env.view.zoom = 1.0f;
	env.view.shift = (t_point){0, 0};
	env.view.rotation = (t_voxel){0.0f, 0.0f, 0.0f};
	env.view.z_scale = 1.0f;
	env.win_height = WINDOW_HEIGHT;
	env.win_width = WINDOW_WIDTH;
	env.menu_width = MENU_WIDTH;
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, env.win_width, env.win_height, "FdF");
	put_window(&env);
	mlx_hook(env.window, 2, 1L, handle_keypress, &env);
	mlx_hook(env.window, 17, 0, free_and_exit, &env);
	mlx_loop(env.mlx);
}
