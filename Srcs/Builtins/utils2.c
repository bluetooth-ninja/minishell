/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:26:11 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/07 15:52:22 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	name_strncmp(const char *name, const char *var, int len)
{
	int	res;

	res = ft_strncmp(name, var, len);
	if (!res)
	{
		if (var[len] == '=')
			return (0);
		res = var[len] - '=';
	}
	return (res);
}

int	error_errno(void)
{
	return (-1);
}

char	**search_env(const char *name, char **env)
{
	char	**cur_env;
	int		i;
	char	**words;
	char	*word;

	words = ft_split(name, '=');
	if (!words)
		return ((char **)1);
	word = words[0];
	i = 0;
	cur_env = 0;
	while (env[i] != 0 && !cur_env)
	{
		if (!ft_strncmp(env[i], word, ft_strlen(word)))
			cur_env = (char **)&env[i];
		i++;
	}
	free_array(words);
	return (cur_env);
}

int	is_correct_var(char *str, int can_eq)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '=' && !can_eq)
		return (0);
	return (1);
}
