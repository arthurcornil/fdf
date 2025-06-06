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

void	draw_fdf(t_map *map)
{
	t_env	env;

	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, 1920, 1080, "FdF");
	mlx_key_hook(env.window, test, &env);
	mlx_loop(env.mlx);
	(void)map;
}
