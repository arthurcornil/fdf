/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:42:51 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/18 17:36:44 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t count)
{
	size_t	*alloc_bytes;

	alloc_bytes = (size_t *)malloc(sizeof(size_t) + count);
	if (!alloc_bytes)
		return (NULL);
	*alloc_bytes = count;
	return ((void *)(alloc_bytes + 1));
}
