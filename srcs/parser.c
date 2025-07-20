/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:45:06 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/19 14:21:33 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

unsigned int	get_width(char **strs)
{
	unsigned int	width;

	width = 0;
	while (strs[width])
		width ++;
	return (width);
}

unsigned int	get_height(char *filename)
{
	int				fd;
	unsigned int	height;
	char			*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error while opening the file");
		close(fd);
		return (0);
	}
	height = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height ++;
	}
	close(fd);
	if (height == 0)
		ft_putendl_fd("Error: Empty file", 2);
	return (height);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;
	int		fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	map->height = get_height(filename);
	if (map->height == 0)
	{
		map->points = NULL;
		free_map(map, EXIT_FAILURE);
	}
	map->points = (int **)malloc(sizeof(int *) * (size_t)map->height);
	ft_bzero(map->points, sizeof(int *) * (size_t)map->height);
	fd = open(filename, O_RDONLY);
	fill_lines(map, fd);
	map->lowest = get_extreme_point(map, is_lower, INT_MAX);
	map->highest = get_extreme_point(map, is_higher, INT_MIN);
	return (map);
}
