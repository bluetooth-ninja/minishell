/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:06:30 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/29 19:36:15 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

char	*search_env_value(const char *name, const char **env)
{
	char	*res;
	int		i;

	i = 0;
	res = 0;
	if (!ft_strncmp(name, "?", 2))
		return (ft_itoa(g_sh_exit));
	while (env[i] != 0 && !res)
	{
		if (!name_strncmp(name, env[i], ft_strlen(name)))
		{
			res = ft_strdup(ft_strchr(env[i], '=') + 1);
			if (!res)
				return (0);
		}
		i++;
	}
	if (res == 0)
		return (ft_strdup(""));
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
		return (ERROR_MALLOC_CODE);
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
		return (ERROR_MALLOC_CODE);
	ft_memcpy(new_env, *env, i * sizeof(char *));
	*env = new_env;
	free_array(*env);
	(*env)[i] = ft_strdup(new_env_var);
	if (!((*env)[i]))
		return (ERROR_MALLOC_CODE);
	return (0);
}

int	change_env_var(const char *new_var, char ***env)
{
	char	**cur_var;

	cur_var = 0;
	cur_var = search_env(new_var, *env);
	if (cur_var == (char **)1)
		return (ERROR_MALLOC_CODE);
	if (cur_var)
	{
		free(*cur_var);
		*cur_var = ft_strdup(new_var);
		if (!(*cur_var))
			return (ERROR_MALLOC_CODE);
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
