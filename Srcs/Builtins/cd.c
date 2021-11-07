/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:39 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/08 02:04:04 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(char **env, t_list *path)
{
	char	*home;
	char	*cd_path;
	int		res;

	home = search_env_value("HOME", (const char **)env);
	if (!home)
		return (1);
	if (!home[0])
		return (2);
	if (path)
	{
		cd_path = ft_strjoin(home, &(((char *)(path->content))[1]));
		free(home);
		if (!cd_path)
			return (1);
		home = cd_path;
	}
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

static int	cd_err(int res, char *tmp)
{
	if (res == 2)
	{
		ft_putendl_fd("minishell: cd: cann't cd", 2);
		return (2);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_sh_exit = 1;
	if (tmp)
		free(tmp);
	return (1);
}

int	do_cd(t_list *line_element, char ***env)
{
	char	*tmp;
	int		res;

	if (line_element && line_element->next)
	{
		ft_putendl_fd("minishell: cd: Too many arguments", 2);
		return (1);
	}
	tmp = getcwd(0, 0);
	if (line_element && ((char *)(line_element->content))[0] != '~')
		res = chdir((char *)line_element->content);
	else
		res = cd_home(*env, line_element);
	if (res == 1)
		return (ERR_CODE);
	if (res)
		return (cd_err(res, tmp));
	res = do_change_env_var("OLDPWD=", tmp, env);
	free(tmp);
	if (res)
		return (ERR_CODE);
	tmp = getcwd(0, 0);
	res = do_change_env_var("PWD=", tmp, env);
	free(tmp);
	return (my_return(res));
}
