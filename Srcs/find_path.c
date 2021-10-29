/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:06:33 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/29 19:07:14 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_path(char **path, char *dir)
{
	char		*temp;
	char		*new_path;
	struct stat	s;

	temp = ft_strjoin("/", *path);
	if (!temp)
		return (ERROR_MALLOC_CODE);
	new_path = ft_strjoin(dir, temp);
	free(temp);
	if (!new_path)
		return (ERROR_MALLOC_CODE);
	if (stat(new_path, &s) == 0)
	{
		free(*path);
		*path = new_path;
		return (1);
	}
	free(new_path);
	return (0);
}

int	find_path(char **path, char **env)
{
	int		i;
	char	*temp;
	char	**paths;
	int		is_find;

	is_find = 0;
	temp = (char *)search_env_value("PATH", (const char **)env);
	if (!temp)
		return (ERROR_MALLOC_CODE);
	paths = ft_split(temp, ':');
	free(temp);
	if (!paths)
		return (ERROR_MALLOC_CODE);
	i = -1;
	while (paths[++i] && !is_find)
		is_find = try_path(path, paths[i]);
	free_array(paths);
	return (is_find);
}
