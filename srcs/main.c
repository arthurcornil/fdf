/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:56:25 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 08:45:11 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int ret2(void)
{
	return 2;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf [PATH TO MAP]", 2);
		exit(EXIT_FAILURE);
	}
	parse_map(argv[1]);
	//draw_fdf();
	return (0);
}
