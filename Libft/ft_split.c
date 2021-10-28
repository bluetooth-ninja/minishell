/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 03:31:16 by vlucilla          #+#    #+#             */
/*   Updated: 2020/11/19 21:49:57 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(char const *s, char c)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			res++;
		i++;
	}
	return (res);
}

static int	ft_chars_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	*ft_empty_arr(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**ft_split_array(char const *s, char c, int w_count, char **arr)
{
	int	i;
	int	w_len;
	int	k;

	i = 0;
	while (i < w_count)
	{
		while (*s == c)
			s++;
		w_len = ft_chars_count(s, c);
		arr[i] = (char *)malloc(sizeof(char) * (w_len + 1));
		if (!arr[i])
			return (ft_empty_arr(arr, i));
		k = 0;
		while (k < w_len)
			arr[i][k++] = *s++;
		arr[i][k] = '\0';
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		len;

	if (!s)
		return (NULL);
	len = ft_words_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr = ft_split_array(s, c, len, arr);
	return (arr);
}
