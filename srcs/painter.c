/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:59:37 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/07 00:03:08 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	put_pixel(t_img *img, t_point pixel, int color)
{
	char	*dst;
	if (pixel.x < 0 || pixel.x >= WINDOW_WIDTH || pixel.y < 0 || pixel.y >= WINDOW_HEIGHT)
		return;

	dst = img->addr + ((pixel.y * img->line_length) + (pixel.x * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	ft_swap_anything(void *a, void *b, size_t size)
{
	unsigned char	tmp;
	size_t			i;

	i = 0;
	while (i < size)
	{
		tmp = ((unsigned char *)a)[i];
		((unsigned char *)a)[i] = ((unsigned char *)b)[i];
		((unsigned char *)b)[i] = tmp;
		i++;
	}
}

static int	get_color(int delta, t_color color_a, t_color color_b, int i)
{
	t_color	color;
	float	percentage;
	
	percentage = get_percentage(i, 0, delta);
	color.red = color_a.red * (1.0f - percentage) + color_b.red * percentage;
	color.green = color_a.green * (1.0f - percentage) + color_b.green * percentage;
	color.blue = color_a.blue * (1.0f - percentage) + color_b.blue * percentage;
	return (color_to_int(color));
}

void draw_vertical_line(t_img *img, t_point a, t_point b, t_color color_a, t_color color_b)
{
	t_point	delta;
	t_point	pixel;
	int		direction;
	int		color;
	int		i;
	int		p;

	if (a.y > b.y)
	{
		ft_swap_anything(&a, &b, sizeof(t_point));
		ft_swap_anything(&color_a, &color_b, sizeof(t_color));
	}
	delta.y = b.y - a.y;
	delta.x = b.x - a.x;
	direction = -1;
	if (delta.x >= 0)
		direction = 1;
	delta.x *= direction;
	if (delta.y > 0)
	{
		p = 2 * delta.x - delta.y;
		pixel = a;
		i = 0;
		while (i < delta.y + 1)
		{
			color = get_color(delta.y, color_a, color_b, i);
			put_pixel(img, pixel, color);
			if (p >= 0)
			{
				pixel.x += direction;
				p -= 2 * delta.y;
			}
			p = p + 2 * delta.x;
			pixel.y ++;
			i ++;
		}
	}
}

void draw_horizontal_line(t_img *img, t_point a, t_point b, t_color color_a, t_color color_b)
{
	t_point	delta;
	t_point	pixel;
	int		direction;
	int		i;
	int		p;
	int		color;

	(void)color_a;
	(void)color_b;
	if (a.x > b.x)
	{
		ft_swap_anything(&a, &b, sizeof(t_point));
		ft_swap_anything(&color_a, &color_b, sizeof(t_color));
	}
	delta.x = b.x - a.x;
	delta.y = b.y - a.y;
	direction = -1;
	if (delta.y >= 0)
		direction = 1;
	delta.y *= direction;
	if (delta.x > 0)
	{
		p = 2 * delta.y - delta.x;
		pixel = a;
		i = 0;
		while (i < delta.x + 1)
		{
			color = get_color(delta.x, color_a, color_b, i);
			put_pixel(img, pixel, color);
			if (p >= 0)
			{
				pixel.y += direction;
				p -= 2 * delta.x;
			}
			p = p + 2 * delta.y;
			pixel.x ++;
			i ++;
		}
	}
}

void	draw_line(t_img *img, t_point a, t_point b, t_color color_a, t_color color_b)
{
	if (abs(b.x - a.x) > abs(b.y - a.y))
	{
		draw_horizontal_line(img, a, b, color_a, color_b);
		return ;
	}
	draw_vertical_line(img, a, b, color_a, color_b);
}
