/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:16:25 by arcornil          #+#    #+#             */
/*   Updated: 2025/03/27 14:22:08 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*newstr;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((start + len) > slen)
		len = slen - start;
	if (start > slen)
		len = 0;
	newstr = malloc(len + 1 * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len && start <= slen)
	{
		newstr[i] = s[start];
		start ++;
		i ++;
	}
	newstr[i] = 0;
	return (newstr);
}
