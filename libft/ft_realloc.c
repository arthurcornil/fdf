/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:53:12 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/18 17:48:30 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	*curr_size;
	void	*newptr;
	size_t	i;

	if (!ptr)
		return (ft_malloc(size));
	curr_size = (size_t *)ptr - 1;
	newptr = ft_malloc(size);
	if (!newptr)
		return (NULL);
	i = 0;
	while (i < size && i < *curr_size)
	{
		((unsigned char *)newptr)[i] = ((unsigned char *)ptr)[i];
		i ++;
	}
	ft_free(ptr);
	return (newptr);
}
