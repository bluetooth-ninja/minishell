/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:54:17 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/18 02:59:56 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*s;
	char	c;
	size_t	i;

	s = (char *)str;
	c = (char)ch;
	i = ft_strlen(str);
	while (i > 0)
	{
		if (s[i] == c)
			return (s + i);
		i--;
	}
	if (s[i] == c)
		return (s);
	return (NULL);
}
