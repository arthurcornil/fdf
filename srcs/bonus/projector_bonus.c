/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:20:17 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/20 10:22:43 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	rotate_z(t_voxel *voxel, t_env *env)
{
	float	tmp_x;
	float	tmp_y;
	float	cx;
	float	cy;

	cx = env->map->width / 2.0f;
	cy = env->map->height / 2.0f;
	tmp_x = voxel->x - cx;
	tmp_y = voxel->y - cy;
	voxel->x = tmp_x * cos(env->view.rotation.z)
		- tmp_y * sin(env->view.rotation.z) + cx;
	voxel->y = tmp_x * sin(env->view.rotation.z)
		+ tmp_y * cos(env->view.rotation.z) + cy;
}

t_point	voxel_to_pixel(t_voxel voxel, t_env *env)
{
	t_point	pixel;
	t_point	projected_pixel;

	rotate_z(&voxel, env);
	if (env->view.zoom < 0.0f)
		env->view.zoom = 0.0f;
	pixel.x = (voxel.x * env->view.zoom * (env->win_width / 2)
			/ env->map->width) + (env->win_width / 3);
	pixel.y = (voxel.y * env->view.zoom * (env->win_height / 2)
			/ env->map->height) - (env->win_height / 3);
	projected_pixel.x = ((pixel.x - pixel.y) * cos(M_PI / 6))
		+ env->view.shift.x;
	projected_pixel.y = ((pixel.x + pixel.y) * sin(M_PI / 6)
			- (voxel.z * env->view.z_scale * env->view.zoom))
		+ env->view.shift.y;
	return (projected_pixel);
}

t_line	get_connector(t_point next_point, t_env *env,
		t_color color1, t_point pixel)
{
	t_color	color2;
	t_voxel	voxel;
	t_point	next_pixel;
	t_line	line;

	color2 = get_color(env->map->points[next_point.y][next_point.x],
			env->map, START_COLOR, END_COLOR);
	voxel = (t_voxel){next_point.x, next_point.y,
		env->map->points[next_point.y][next_point.x]};
	next_pixel = voxel_to_pixel(voxel, env);
	line = get_line(color1, color2, pixel, next_pixel);
	return (line);
}

void	connect_next_point(t_connect_next_point_params params)
{
	t_point	point;
	t_env	*env;
	t_color	color;
	t_point	pixel;
	t_line	line;

	point = params.point;
	env = params.env;
	color = params.color;
	pixel = params.pixel;
	if (point.x < (int)(env->map->width - 1))
	{
		line = get_connector((t_point)
			{point.x + 1, point.y}, env, color, pixel);
		draw_line(params.img, &line);
	}
	if (point.y < (int)(env->map->height - 1))
	{
		line = get_connector((t_point)
			{point.x, point.y + 1}, env, color, pixel);
		draw_line(params.img, &line);
	}
}

void	draw_fdf(t_env *env, t_img *img)
{
	unsigned int	x;
	unsigned int	y;
	t_point			pixel;
	t_color			color;

	y = 0;
	while (y < env->map->height)
	{
		x = 0;
		while (x < env->map->width)
		{
			color = get_color(env->map->points[y][x],
					env->map, START_COLOR, END_COLOR);
			pixel = voxel_to_pixel(
					(t_voxel){x, y, env->map->points[y][x]},
					env
					);
			connect_next_point((t_connect_next_point_params)
			{(t_point){x, y}, env, color, pixel, img});
			x ++;
		}
		y ++;
	}
}
