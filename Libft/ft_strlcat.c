/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 03:14:29 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/20 03:37:29 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, const char *src, int nb)
{
	int	i;
	int	d_size;

	i = 0;
	d_size = 0;
	while (dest[d_size] != '\0')
		d_size++;
	while (i < nb && src[i] != '\0')
	{
		dest[d_size] = src[i];
		d_size++;
		i++;
	}
	dest[d_size] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	if (size > d_len)
		ft_strncat(dest, (char *)src, size - d_len - 1);
	if (d_len <= size)
		return (d_len + s_len);
	else
		return (size + s_len);
}
