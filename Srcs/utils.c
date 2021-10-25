/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:56:23 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 23:42:20 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	env_cpy(char ***my_env, char **env)
{
	int	i;

	i = 0;
	if (!my_env)
		return (1);
	while (env[i] != 0)
		i++;
	*my_env = malloc(sizeof(char *) * (i + 1));
	(*my_env)[i] = 0;
	i--;
	while (i >= 0)
	{
		(*my_env)[i] = ft_strdup(env[i]);
		i--;
	}
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

char	*substr_word(char *str, const char *delims)
{
	char	*word;
	int		i;

	word = NULL;
	if (!str)
		return (0);
	i = 0;
	while (!ft_strchr(delims, str[i]))
		i++;
	if (i > 0)
	{
		word = (char *)malloc(sizeof(char) * i);
		if (!word)
			return (0);
		ft_strlcpy(word, str, i);
	}
	return (word);
}
