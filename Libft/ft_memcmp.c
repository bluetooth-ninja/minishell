/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 04:22:08 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/19 18:04:11 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*ptr_arr1;
	unsigned char	*ptr_arr2;
	size_t			i;

	ptr_arr1 = (unsigned char *)arr1;
	ptr_arr2 = (unsigned char *)arr2;
	i = 0;
	while (i < n)
	{
		if (ptr_arr1[i] != ptr_arr2[i])
			return (ptr_arr1[i] - ptr_arr2[i]);
		i++;
	}
	return (0);
}
