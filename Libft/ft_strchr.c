/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 03:29:19 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/18 03:30:39 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int ch)
{
	char	*s1;

	s1 = (char *)s;
	while (*s1)
	{
		if (*s1 == ch)
			return (s1);
		s1++;
	}
	if (*s1 == '\0' && ch == '\0')
		return (s1);
	return (NULL);
}
