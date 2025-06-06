/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:54:43 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/10 15:15:53 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	nbrlen(int n)
{
	unsigned int	nbrlen;

	nbrlen = 1;
	while (n <= -10 || n >= 10)
	{
		nbrlen++;
		n /= 10;
	}
	return (nbrlen);
}

static char	*init_str(unsigned int ndigits, unsigned int i, long nbr)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (ndigits + i + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
		str[0] = '-';
	str[ndigits + i] = (char)0;
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num_digits;
	unsigned int	i;
	long			nbr;

	nbr = n;
	num_digits = nbrlen(n);
	i = 0;
	if (nbr < 0)
		i = 1;
	str = init_str(num_digits, i, nbr);
	if (!str)
		return (NULL);
	if (nbr < 0)
		nbr = -nbr;
	if (!str)
		return (NULL);
	while (num_digits > 0)
	{
		str[i + num_digits - 1] = (nbr % 10) + '0';
		nbr /= 10;
		num_digits --;
	}
	return (str);
}
