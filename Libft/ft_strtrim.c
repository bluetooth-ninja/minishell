/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:49:16 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/20 18:30:14 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charinset(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	s1_start;
	size_t	s1_end;
	size_t	i;

	i = 0;
	s1_start = 0;
	if (!s1 || !set)
		return (NULL);
	s1_end = ft_strlen(s1);
	while (s1[s1_start] && (ft_charinset(set, s1[s1_start])))
		s1_start++;
	while (s1_end > s1_start && (ft_charinset(set, s1[s1_end - 1])))
		s1_end--;
	str = (char *)malloc(sizeof(char) * (s1_end - s1_start + 1));
	if (!str)
		return (NULL);
	while (s1_start < s1_end)
		str[i++] = s1[s1_start++];
	str[i] = '\0';
	return (str);
}
