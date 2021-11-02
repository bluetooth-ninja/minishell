/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:39 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/02 01:04:18 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(char **env)
{
	char	*home;
	int		res;

	home = search_env_value("HOME", (const char **)env);
	if (!home)
		return (1);
	res = chdir(home);
	free(home);
	return (res);
}

static int	my_return(int res)
{
	if (res)
		return (ERR_CODE);
	return (0);
}

static int	do_change_env_var(const char *name, const char *value, char ***env)
{
	char	*join;
	int		res;

	join = ft_strjoin(name, value);
	if (!join)
		return (1);
	res = change_env_var(join, env);
	free(join);
	return (res);
}

int	do_cd(t_list *line_element, char ***env)
{
	char	*tmp;
	int		res;

	tmp = getcwd(0, 0);
	if (line_element && ft_strncmp(line_element->content, "~", 2))
		res = chdir((char *)line_element->content);
	else
		res = cd_home(*env);
	if (res == 1)
		return (ERR_CODE);
	if (res)
	{
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
		g_sh_exit = 1;
		free(tmp);
		return (1);
	}
	res = do_change_env_var("OLDPWD=", tmp, env);
	free(tmp);
	if (res)
		return (ERR_CODE);
	tmp = getcwd(0, 0);
	res = do_change_env_var("PWD=", tmp, env);
	free(tmp);
	return (my_return(res));
}
