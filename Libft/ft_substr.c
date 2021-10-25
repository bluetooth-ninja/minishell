/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:45:49 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/20 04:03:30 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	j;
	size_t	k;
	size_t	s_start;

	s_start = (size_t)start;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= s_start)
		len = 0;
	if (ft_strlen(s) - s_start < len)
		len = ft_strlen(s) - s_start;
	j = len + s_start;
	k = 0;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while ((s_start < j) && (*s != '\0'))
		substr[k++] = s[s_start++];
	substr[k] = '\0';
	return (substr);
}
