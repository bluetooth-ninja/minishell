/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:19:47 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/08 01:15:41 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_type(char *str)
{
	char	*tmp;

	tmp = ft_strchrq(str, '<');
	str = ft_strchrq(str, '>');
	if (!tmp && !str)
		return (0);
	if ((tmp < str && tmp) || !str)
		str = tmp;
	if (str[0] == '>' && str[1] != '<' && str[1] != '>')
		return (R_RDR);
	if (str[0] == '<' && str[1] != '<' && str[1] != '>')
		return (L_RDR);
	if (!str[1])
		return (0);
	if (str[0] == '>' && str[1] == '>' && str[2] != '<' && str[2] != '>')
		return (DR_RDR);
	if (str[0] == '<' && str[1] == '<' && str[2] != '<' && str[2] != '>')
		return (DL_RDR);
	return (0);
}

static int	result(int res)
{
	if (res == -2)
	{
		g_sh_exit = 2;
		return (2);
	}
	if (res == -3)
	{
		g_sh_exit = 1;
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		return (1);
	}
	return (ERR_CODE);
}

static int	error_for_rita(char *file)
{
	if (*file)
	{
		ft_putendl_fd("minishell: Syntax error", 2);
		g_sh_exit = 2;
	}
	else
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		g_sh_exit = 1;
	}
	if (file)
		free(file);
	return (g_sh_exit);
}

int	parse_redir(t_list *com, char ***env)
{
	int		type;
	char	*file;
	int		res;
	char	**str;

	str = &(((t_command *)(com->content))->text);
	res = 0;
	type = find_type(*str);
	if (!type)
	{
		ft_putendl_fd("minishell: Syntax error", 2);
		return (result(-2));
	}
	res = cut_file(str, &file, type, *env);
	if (res)
		return (result(res));
	if (!(*file) || *file == '<' || *file == '>')
		return (error_for_rita(file));
	else
		res = do_redirects(type, file, com, env);
	free(file);
	return (res);
}
