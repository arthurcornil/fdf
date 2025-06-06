/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:45:06 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 10:37:31 by arcornil         ###   ########.fr       */
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

int	*parse_line(char *line)
{
	char				**strs;
	int					*nums;
	static unsigned int	width = 0;
	unsigned int		i;

	strs = ft_split(line, ' ');
	if (!strs)
		return (NULL);
	if (width == 0)
		width = get_width(strs);
	else if (width != get_width(strs))
		return (NULL);
	nums = (int *)malloc(sizeof(int) * (size_t)width);
	if (!nums)
		return (NULL);
	i = 0;
	while (i < width)
	{
		nums[i] = ft_atoi(strs[i]);
		i ++;
	}
	return (nums);
}

unsigned int	get_height(char *filename)
{
	int				fd;
	unsigned int	height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error while opening the file");
		close(fd);
		return (0);
	}
	height = 0;
	while (get_next_line(fd))
		height ++;
	close(fd);
	if (height == 0)
		ft_putendl_fd("Error: Empty file", 2);
	return (height);
}

void	fill_points(t_map *map, char *filename)
{
	int				fd;
	unsigned int	i;
	char			*line;

	map->width = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error while opening the file");
		free_map(map, EXIT_FAILURE);
	}
	i = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (map->width == 0)
			map->width = get_width(ft_split(line, ' ')); //TODO: MAYBE CHANGE THIS LINE?
		map->points[i] = parse_line(line);
		if (!map->points[i])
		{
			free(line);
			while (get_next_line(fd))
				;
			close(fd);
			free_map(map, EXIT_FAILURE);
		}
		free(line);
		i ++;
	}
	close(fd);
}

t_map	*parse_map(char *filename)
{
	t_map			*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	map->height = get_height(filename);
	if (map->height == 0)
		free_map(map, EXIT_FAILURE);
	map->points = (int **)malloc(sizeof(int *) * (size_t)map->height);
	ft_bzero(map->points, sizeof(int *) * (size_t)map->height);
	fill_points(map, filename);
	return (map);
}
