/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 03:00:37 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/18 03:04:32 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	g_len;

	if (s2[0] == '\0')
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	g_len = s1_len > len ? len : s1_len;
	if (len < s2_len || s2_len > s1_len)
		return (NULL);
	while (g_len-- >= s2_len)
	{
		if (ft_strncmp(s1, s2, s2_len) == 0)
			return (char *)s1;
		s1++;
	}
	return (NULL);
}
