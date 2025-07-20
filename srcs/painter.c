/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:59:37 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/19 21:00:05 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	put_pixel(t_img *img, t_point pixel, int color)
{
	char	*dst;

	if (pixel.x < MENU_WIDTH || pixel.x >= WINDOW_WIDTH
		|| pixel.y < 0 || pixel.y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + ((pixel.y * img->line_length)
			+ (pixel.x * (img->bits_per_pixel / 8)));
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

static void	put_line_pixels(t_img *img, t_line *line, bool is_steep)
{
	t_line_loop_params	params;

	params.img = img;
	params.line = line;
	params.dx = line->pixel_b.x - line->pixel_a.x;
	if (line->pixel_b.y < line->pixel_a.y)
		params.direction = -1;
	else
		params.direction = 1;
	params.pixel = line->pixel_a;
	params.is_steep = is_steep;
	put_line_pixels_loop(&params);
}

void	draw_line(t_img *img, t_line *line)
{
	bool	is_steep;

	is_steep = abs(line->pixel_b.y - line->pixel_a.y)
		> abs(line->pixel_b.x - line->pixel_a.x);
	if (is_steep)
	{
		ft_swap_anything(&line->pixel_a.x, &line->pixel_a.y, sizeof(int));
		ft_swap_anything(&line->pixel_b.x, &line->pixel_b.y, sizeof(int));
	}
	if (line->pixel_a.x > line->pixel_b.x)
	{
		ft_swap_anything(&line->pixel_a, &line->pixel_b, sizeof(t_point));
		ft_swap_anything(&line->color_a, &line->color_b, sizeof(t_color));
	}
	put_line_pixels(img, line, is_steep);
}
