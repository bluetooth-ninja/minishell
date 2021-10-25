/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 01:20:02 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/18 01:23:33 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*ptr_arr;
	size_t			i;

	ptr_arr = (unsigned char *)arr;
	i = 0;
	while (i < n)
	{
		if (ptr_arr[i] == (unsigned char)c)
			return (ptr_arr + i);
		i++;
	}
	return (NULL);
}
