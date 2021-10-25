/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 03:27:52 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/20 03:18:32 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*str1;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	str1 = (char *)malloc((len + 1) * sizeof(char));
	if (!str1)
		return (NULL);
	else
	{
		while (str[i] != '\0')
		{
			str1[i] = str[i];
			i++;
		}
		str1[i] = '\0';
	}
	return (str1);
}
