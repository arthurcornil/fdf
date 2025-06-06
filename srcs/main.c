/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:56:25 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/07 00:22:49 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf [PATH TO MAP]", 2);
		exit(EXIT_FAILURE);
	}
	map = parse_map(argv[1]);
	render(map);
	return (0);
}
