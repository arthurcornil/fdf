/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:12:12 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/20 10:22:29 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float	get_percentage(int current, int min, int max)
{
	if (max == min)
		return (0.0f);
	return ((float)(current - min) / (float)(max - min));
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

t_color	get_color(int z, t_map *map, int start, int end)
{
	float	percentage;
	t_color	color_start;
	t_color	color_end;
	t_color	color;

	percentage = get_percentage(z, map->lowest, map->highest);
	color_start = int_to_color(start);
	color_end = int_to_color(end);
	color.red = color_start.red
		+ ((color_end.red - color_start.red) * percentage);
	color.green = color_start.green
		+ ((color_end.green - color_start.green) * percentage);
	color.blue = color_start.blue
		+ ((color_end.blue - color_start.blue) * percentage);
	return (color);
}

t_line	get_line(t_color color_a, t_color color_b,
		t_point pixel_a, t_point pixel_b)
{
	return (
		(t_line){
		color_a,
		color_b,
		pixel_a,
		pixel_b
	}
	);
}
