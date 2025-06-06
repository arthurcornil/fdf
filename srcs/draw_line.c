/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:59:37 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/07 00:03:08 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + ((y * img->line_length) + (x * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	draw_line(t_point origin, t_point dest, t_img *img)
{
	t_point	delta;
	t_point	point;
	t_point	step;
	int		decision;
	int		decision2;

	delta.x = abs(dest.x - origin.x);
	delta.y = abs(dest.y - origin.y);
	point = origin;
	step.x = (dest.x >= origin.x) ? 1 : -1;
	step.y = (dest.y >= origin.y) ? 1 : -1;
	decision = (delta.x > delta.y ? delta.x : -delta.y) / 2;
	while (true)
	{
		put_pixel(img, point.x, point.y, 0x000000FF);
		if (point.x == dest.x && point.y == dest.y)
			break ;
		decision2 = decision;
		if (decision2 > -delta.x)
		{
			decision -= delta.y;
			point.x += step.x;
		}
		if (decision2 < delta.y)
		{
			decision += delta.x;
			point.y += step.y;
		}
	}
}
