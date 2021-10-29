/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:39 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/29 19:37:30 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_cd(t_list *line_element, char ***env)
{
	char	*tmp;
	int		res;

	tmp = getcwd(0, 0);
	if (line_element)
		res = chdir((char *)line_element->content);
	else
		res = chdir("~");
	if (res)
	{
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
		g_sh_exit = 1;
		return (1);
	}
	res = change_env_var(ft_strjoin("OLDPWD=", tmp), env);
	free(tmp);
	if (res)
		return (ERROR_MALLOC_CODE);
	tmp = getcwd(0, 0);
	res = change_env_var(ft_strjoin("PWD=", tmp), env);
	free(tmp);
	if (res)
		return (ERROR_MALLOC_CODE);
	return (0);
}
