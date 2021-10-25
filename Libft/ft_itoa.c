/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 01:06:40 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/20 16:35:43 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numb_size(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb = -1 * nb;
		i += 1;
	}
	if (nb == 0)
		i = 1;
	while (nb > 0)
	{
		nb = nb / 10;
		i = i + 1;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	x;

	x = (long)n;
	i = numb_size(x);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		x = -1 * x;
		str[0] = '-';
	}
	if (x == 0)
		str[0] = '0';
	while (x > 0)
	{
		str[i - 1] = x % 10 + '0';
		x = x / 10;
		i--;
	}
	return (str);
}
