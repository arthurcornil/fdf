/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:58:24 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/19 21:01:32 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_interval_color(int delta, t_color color_a,
		t_color color_b, int i)
{
	t_color	color;
	float	percentage;

	percentage = get_percentage(i, 0, delta);
	color.red = color_a.red * (1.0f - percentage) + color_b.red * percentage;
	color.green = color_a.green * (1.0f - percentage)
		+ color_b.green * percentage;
	color.blue = color_a.blue * (1.0f - percentage) + color_b.blue * percentage;
	return (color_to_int(color));
}

static void	put_pixel_steep(t_img *img, t_point pixel, int color, bool is_steep)
{
	if (is_steep)
		put_pixel(img, (t_point){pixel.y, pixel.x}, color);
	else
		put_pixel(img, pixel, color);
}

void	put_line_pixels_loop(t_line_loop_params *p)
{
	int		dy;
	int		p_err;
	int		color;
	int		i;

	dy = abs(p->line->pixel_b.y - p->line->pixel_a.y);
	p_err = 2 * dy - p->dx;
	i = 0;
	while (i <= p->dx)
	{
		color = get_interval_color(p->dx, p->line->color_a,
				p->line->color_b, i);
		put_pixel_steep(p->img, p->pixel, color, p->is_steep);
		if (p_err >= 0)
		{
			p->pixel.y += p->direction;
			p_err -= 2 * p->dx;
		}
		p_err += 2 * dy;
		p->pixel.x++;
		i++;
	}
}
