/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <vlucilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:13:33 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/24 17:59:07 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_words_count(char const *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t' && (s[i + 1] == ' '
				|| s[i + 1] == '\t' || s[i + 1] == '\0'))
			res++;
		i++;
	}
	return (res);
}

static int	ft_chars_count(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
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

static char	**ft_split_array(char const *s, int w_count, char **arr)
{
	int	i;
	int	w_len;
	int	k;

	i = 0;
	while (i < w_count)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		w_len = ft_chars_count(s);
		arr[i] = (char *)malloc(sizeof(char) * (w_len + 1));
		if (!arr[i])
			return (ft_empty_arr(arr, i));
		k = 0;
		while (k < w_len)
			if (*s == 1)
				arr[i][k++] = ' ';
			else
				arr[i][k++] = *s++;
		arr[i][k] = '\0';
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	**space_split(char const *s)
{
	char	**arr;
	int		len;

	if (!s)
		return (NULL);
	len = ft_words_count(s);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr = ft_split_array(s, len, arr);
	return (arr);
}
