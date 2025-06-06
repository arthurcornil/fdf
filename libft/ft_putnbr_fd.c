/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcornil <arcornil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:55:18 by arcornil          #+#    #+#             */
/*   Updated: 2025/04/10 15:56:42 by arcornil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_factor(int n)
{
	int	factor;

	factor = 1;
	while (n >= 10)
	{
		n /= 10;
		factor *= 10;
	}
	return (factor);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		factor;
	char	digit;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	factor = find_factor(n);
	while (factor != 0)
	{
		digit = (n / factor) + '0';
		write(fd, &digit, 1);
		n %= factor;
		factor /= 10;
	}
}
