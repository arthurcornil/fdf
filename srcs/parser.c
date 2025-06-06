/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:45:06 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 08:52:20 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

unsigned int	get_width(char **strs)
{
	unsigned int	width;

	width = 0;
	while(strs[width])
		width ++;
	return (width);
}

int		*parse_line(char *line)
{
	char				**strs;
	int					*nums;
	static unsigned int	width = 0;
	unsigned int		i;

	strs = ft_split(line, ' '); // TODO:	CHECK ERROR MALLOCS
	if (width == 0)
		width = get_width(strs);
	else if (width != get_width(strs))
	{
		exit(EXIT_FAILURE);
		//TOO: EXIT
	}
	nums = (int *)malloc(sizeof(int) * (size_t)width);
	if (!nums)
	{
		exit(EXIT_FAILURE);
		//TODO: EXIT
	}
	i = 0;
	while (i < width)
	{
		nums[i] = ft_atoi(strs[i]);
		i ++;
	}
	return (nums);
}

t_map	*parse_map(char *filename)
{
	char				*line;
	t_map				*map;
	int					fd;
	unsigned int		i;

	fd = open(filename, O_RDONLY);
	//TODO: CHECK FD
	i = 0;
	while ((line = get_next_line(fd)))
		i ++;
	close(fd);
	if (i == 0)
	{
		exit(EXIT_FAILURE);
		//TODO: MANAGE ERROR
	}
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		exit(EXIT_FAILURE);
		//TODO: MANAGE ERROR
	}
	map->height = i;
	map->points = (int **)malloc(sizeof(int *) * (size_t)map->height);
	map->width = 0;
	fd = open(filename, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (map->width == 0)
			map->width = get_width(ft_split(line, ' '));
		map->points[i] = parse_line(line);
		i ++;
	}
	printf("Map Height: %u\n", map->height);
	printf("Map Width: %u\n", map->width);

	return (map);
}
