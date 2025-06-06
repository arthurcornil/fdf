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

t_point voxel_to_pixel(t_voxel voxel, t_env *env)
{
    t_point pixel;
    float projected_x = voxel.x * env->zoom / voxel.z;
    float projected_y = voxel.y * env->zoom / voxel.z;
    pixel.x = (int)((projected_x + 1.0f) * (WINDOW_WIDTH / 2.0f));
    pixel.y = (int)((1.0f - projected_y) * (WINDOW_HEIGHT / 2.0f));
    return pixel;
}

void	draw_fdf(t_env *env)
{
	t_img	img;

	img.ptr = mlx_new_image(env->mlx, env->win_width, env->win_height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

	t_voxel	vAf = (t_voxel){-2, -0.5, 5};
	t_voxel	vBf = (t_voxel){-2,  0.5, 5};
	t_voxel	vCf = (t_voxel){-1,  0.5, 5};
	t_voxel	vDf = (t_voxel){-1, -0.5, 5};
	t_voxel	vAb = (t_voxel){-2, -0.5, 8};
	t_voxel	vBb = (t_voxel){-2,  0.5, 8};
	t_voxel	vCb = (t_voxel){-1,  0.5, 8};
	t_voxel	vDb = (t_voxel){-1, -0.5, 8};
	draw_line(voxel_to_pixel(vAf, env), voxel_to_pixel(vBf, env), &img);
	draw_line(voxel_to_pixel(vBf, env), voxel_to_pixel(vCf, env), &img);
	draw_line(voxel_to_pixel(vCf, env), voxel_to_pixel(vDf, env), &img);
	draw_line(voxel_to_pixel(vDf, env), voxel_to_pixel(vAf, env), &img);
	draw_line(voxel_to_pixel(vAb, env), voxel_to_pixel(vBb, env), &img);
	draw_line(voxel_to_pixel(vBb, env), voxel_to_pixel(vCb, env), &img);
	draw_line(voxel_to_pixel(vCb, env), voxel_to_pixel(vDb, env), &img);
	draw_line(voxel_to_pixel(vDb, env), voxel_to_pixel(vAb, env), &img);
	draw_line(voxel_to_pixel(vAf, env), voxel_to_pixel(vAb, env), &img);
	draw_line(voxel_to_pixel(vBf, env), voxel_to_pixel(vBb, env), &img);
	draw_line(voxel_to_pixel(vCf, env), voxel_to_pixel(vCb, env), &img);
	draw_line(voxel_to_pixel(vDf, env), voxel_to_pixel(vDb, env), &img);
	draw_line(voxel_to_pixel(vBf, env), voxel_to_pixel(vDb, env), &img);
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
