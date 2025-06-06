/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:10:42 by arcornil          #+#    #+#             */
/*   Updated: 2025/06/06 08:52:13 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>

typedef struct	s_map
{
	unsigned int	height;
	unsigned int	width;
	int				**points;
}	t_map;

t_map	*parse_map(char *filename);

#endif
