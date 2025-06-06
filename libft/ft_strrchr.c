/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:37:52 by arcornil          #+#    #+#             */
/*   Updated: 2025/03/27 08:39:03 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*target;

	target = NULL;
	while (*s)
	{
		if (*s == (char)c)
			target = (char *)s;
		s ++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (target);
}
