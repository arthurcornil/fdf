/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:36:54 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/21 09:36:02 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_gnl_buffer(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	close(fd);
}

void	free_strs(char **strs)
{
	unsigned int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i ++;
	}
	if (strs)
		free(strs);
}

void	free_map(t_map *map, int exit_status)
{
	unsigned int	i;

	if (!map)
		return ;
	i = 0;
	while (map->points && i < map->height)
	{
		if (map->points[i])
			free(map->points[i]);
		i ++;
	}
	if (map->points)
		free(map->points);
	free(map);
	if (exit_status > 0)
		exit(exit_status);
}

int	free_and_exit(t_env *env)
{
	free_map(env->map, -1);
	mlx_destroy_window(env->mlx, env->window);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit(EXIT_SUCCESS);
}
