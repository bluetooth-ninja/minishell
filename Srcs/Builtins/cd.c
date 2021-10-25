/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:39 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 22:05:25 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../Libft/libft.h"

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
		return (1);			//Ошибка
	change_env_var(ft_strjoin("OLDPWD=", tmp), env);
	free(tmp);
	tmp = getcwd(0, 0);
	change_env_var(ft_strjoin("PWD=", tmp), env);
	free(tmp);
	return (0);
}
