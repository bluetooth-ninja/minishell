/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:19:47 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/30 03:54:12 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_type(char *str)
{
	char	*tmp;

	tmp = ft_strchrq(str, '<');
	str = ft_strchrq(str, '>');
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
		g_sh_exit = 1;
		return (0);
	}
	res = cut_file(str, &file, type);
	if (res)
		return (ERROR_MALLOC_CODE);
	if (!(*file) || *file == '<' || *file == '>')
		ft_putendl_fd("minishell: Syntax error", 2);
	if (!(*file) || *file == '<' || *file == '>')
		g_sh_exit = 1;
	else
		res = do_redirects(type, file, com, env);
	free(file);
	return (res);
}
