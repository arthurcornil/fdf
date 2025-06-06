/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:36:54 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 10:37:03 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_map(t_map *map, int exit_status)
{
	unsigned int	i;

	if (!map)
		return ;
	i = 0;
	while (map->points && map->points[i])
	{
		free(map->points[i]);
		i ++;
	}
	if (map->points)
		free(map->points);
	free(map);
	if (exit_status > 0)
		exit(exit_status);
}
