/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:19:31 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/10 15:17:12 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_strs_len(char const *s, char c)
{
	unsigned int	num_words;
	bool			found_word;

	num_words = 0;
	found_word = false;
	while (*s)
	{
		while (*s != c && *s)
		{
			if (!found_word)
				found_word = true;
			s ++;
		}
		if (found_word)
			num_words ++;
		while (*s == c && *s)
			s ++;
	}
	return (num_words);
}

static size_t	get_strlen(const char *s, char c)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != c && s[strlen])
		strlen ++;
	return (strlen);
}

static bool	copy_str(char const *s, char c, char **str, size_t *i)
{
	size_t	curr_strlen;

	while (s[*i] == c && s[*i])
		(*i)++;
	curr_strlen = get_strlen(&(s[*i]), c);
	*str = (char *)malloc(sizeof(char) * (curr_strlen + 1));
	if (!str)
		return (0);
	ft_strlcpy(*str, s + *i, curr_strlen + 1);
	*i += curr_strlen;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	unsigned int	strs_len;
	size_t			i;
	size_t			j;

	if (!s)
		return (NULL);
	strs_len = get_strs_len(s, c);
	strs = (char **)malloc(sizeof(char *) * (strs_len + 1));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (i < strs_len)
	{
		if (!copy_str(s, c, &strs[i], &j))
			return (NULL);
		i ++;
	}
	*(strs + i) = NULL;
	return (strs);
}
