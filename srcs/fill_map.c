/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:58:19 by arcornil          #+#    #+#             */
/*   Updated: 2025/07/19 14:00:09 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	*parse_line(char *line)
{
	char				**strs;
	int					*nums;
	static unsigned int	width = 0;

	strs = ft_split(line, ' ');
	if (!strs)
		return (NULL);
	if (width == 0)
		width = get_width(strs);
	else if (!is_same_width(strs, width))
		return (NULL);
	nums = get_nums(strs, width);
	if (!nums)
		return (NULL);
	return (nums);
}

bool	fill_points(t_map *map, unsigned int i, int fd)
{
	char	**strs;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (false);
	line[ft_strlen(line) - 1] = (char)0;
	strs = ft_split(line, ' ');
	if (map->width == 0)
		map->width = get_width(strs);
	map->points[i] = parse_line(line);
	free(line);
	free_strs(strs);
	return (true);
}

void	fill_lines(t_map *map, int fd)
{
	unsigned int	i;

	map->width = 0;
	if (fd < 0)
	{
		perror("Error while opening the file");
		free_map(map, EXIT_FAILURE);
	}
	i = 0;
	while (true)
	{
		if (!fill_points(map, i, fd))
			break ;
		if (!map->points[i])
		{
			while (get_next_line(fd))
				;
			close(fd);
			free_map(map, EXIT_FAILURE);
		}
		i ++;
	}
	close(fd);
}
