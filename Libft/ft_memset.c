/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 01:26:46 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/18 01:28:01 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	unsigned char	*ptr;
	unsigned char	val1;
	size_t			i;

	ptr = (unsigned char *)memptr;
	val1 = (unsigned char)val;
	i = 0;
	while (i < num)
	{
		ptr[i] = val1;
		i++;
	}
	return (memptr);
}
