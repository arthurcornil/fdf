/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:00:06 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 11:09:02 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	test(int key, t_env *env)
{
	if (key == 53)
		mlx_destroy_window(env->mlx, env->window);
	return (0);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + ((y * img->line_length) + (x * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	draw_fdf(t_map *map)
{
	t_env				env;
	unsigned int		x;		
	unsigned int		y;		

	env.padding = WINDOW_PADDING;
	env.win_height = WINDOW_HEIGHT;
	env.win_width = WINDOW_WIDTH;
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, env.win_width, env.win_height, "FdF");
	env.img.ptr = mlx_new_image(env.mlx, env.win_width, env.win_height);
	env.img.addr = mlx_get_data_addr(env.img.ptr, &(env.img.bits_per_pixel), &(env.img.line_length), &(env.img.endian));

	y = 0;
	int color = 0x0000FF00;
	while (y < map->height)
	{ 
		x = 0;
		while (x < map->width)
		{
			put_pixel(&env.img, x * (env.win_width / map->width), y * (env.win_height / map->height), color);
			printf("x: %d, y: %d\n", x * (env.win_width / map->width), y * (env.win_height / map->height));
			x ++;
		}
		y ++;
	}
	
	mlx_put_image_to_window(env.mlx, env.window, env.img.ptr, 0, 0);
	mlx_key_hook(env.window, test, &env);
	mlx_loop(env.mlx);
}
