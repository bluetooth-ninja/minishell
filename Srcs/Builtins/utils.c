/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:06:30 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 17:54:28 by wgaunt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

const char	*search_env_value(const char *name, const char **env)
{
	const char	*res;
	int			i;

	i = 0;
	res = 0;
	while (env[i] != 0 && !res)
	{
		if (!name_strncmp(name, env[i], ft_strlen(name)))
			res = ft_strchr(env[i], '=') + 1;
		i++;
	}
	return (res);
}

int	remove_var(const char *var, char ***env)
{
	int		i;
	char	**new_env;
	int		i_del;

	i = -1;
	i_del = -1;
	while ((*env)[++i])
		if (!name_strncmp(var, (*env)[i], ft_strlen(var)))
			i_del = i;
	if (i_del == -1)
		return (0);
	new_env = ft_calloc(i, sizeof(char *));
	if (new_env == 0)
		return (1);
	i = -1;
	while ((*env)[++i])
	{
		if (i < i_del)
			new_env[i] = (*env)[i];
		else if (i > i_del)
			new_env[i - 1] = (*env)[i];
	}
	free(*env);
	*env = new_env;
	return (0);
}

int	add_env(const char *new_env_var, char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (new_env == 0)
		return (1);
	ft_memcpy(new_env, *env, i * sizeof(char *));
	*env = new_env;
	(*env)[i] = ft_strdup(new_env_var);
	return (0);
}

int	change_env_var(const char *new_var, char ***env)
{
	char	**cur_var;

	cur_var = 0;
	cur_var = search_env(new_var, *env);
	if (cur_var)
	{
		free(*cur_var);
		*cur_var = ft_strdup(new_var);
	}
	else
		return (add_env(new_var, env));
	return (0);
}

char	**search_env(const char *name, char **env)
{
	char	**cur_env;
	int		i;
	char	**words;
	char	*word;

	words = ft_split(name, '=');
	word = words[0];
	i = 0;
	cur_env = 0;
	while (env[i] != 0 && !cur_env)
	{
		if (!ft_strncmp(env[i], word, ft_strlen(word)))
			cur_env = (char **)&env[i];
		i++;
	}
	i = 1;
	while (word)
	{
		free(word);
		word = words[i];
		i++;
	}
	free(words);
	return (cur_env);
}
