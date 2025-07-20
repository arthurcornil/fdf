/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:32:30 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/19 22:10:39 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	is_lower(int a, int b)
{
	return (a < b);
}

int	is_higher(int a, int b)
{
	return (a > b);
}

int	get_extreme_point(t_map *map, t_cmp_ft cmp, int init_val)
{
	unsigned int	x;
	unsigned int	y;
	int				curr_extreme;

	y = 0;
	curr_extreme = init_val;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (cmp(map->points[y][x], curr_extreme))
				curr_extreme = map->points[y][x];
			x ++;
		}
		y ++;
	}
	return (curr_extreme);
}

bool	is_same_width(char **strs, unsigned int expected_width)
{
	unsigned int	curr_width;

	curr_width = get_width(strs);
	if (curr_width != expected_width)
	{
		free_strs(strs);
		return (false);
	}
	return (true);
}

int	*get_nums(char	**strs, unsigned int width)
{
	int				*nums;
	unsigned int	i;

	nums = (int *)malloc(sizeof(int) * (size_t)width);
	if (!nums)
	{
		free_strs(strs);
		return (NULL);
	}
	i = 0;
	while (i < width)
	{
		nums[i] = ft_atoi(strs[i]);
		i ++;
	}
	free(strs);
	return (nums);
}
