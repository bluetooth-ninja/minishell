/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:19:47 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/28 03:20:42 by vlucilla         ###   ########.fr       */
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

int	parse_redir(char *str, char ***env)
{
	int	type;
	char	*file;
	int	res;

	res = 0;
	(void)env;
	type = find_type(str);
	if (!type)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		sh_exit = 1;
		return (-1);
	}
	cut_file(&str, &file, type);
	res = do_redirects(type, file, str, env);
	return (res);
}
