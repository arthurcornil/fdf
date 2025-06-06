/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:32:51 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/14 21:12:52 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*start_dest;

	start_dest = dest;
	while (*src != 0)
	{
		*dest = *src;
		dest ++;
		src ++;
	}
	*dest = 0;
	return (start_dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	dest_len;

	dest_len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * dest_len + 1);
	if (!dest)
		return (NULL);
	return (ft_strcpy(dest, src));
}
