/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:11:36 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/26 00:14:88 by wgaunt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*take_file(char *redir_p, char *endfile_p)
{
	char	*file;
	char	*tmp;

	while (*redir_p == '<' || *redir_p == '>')
		redir_p++;
	while (*redir_p == ' ')
		redir_p++;
	file = (char *)ft_calloc(endfile_p - redir_p + 1, sizeof(char));
	if (!file)
		return (0);
	tmp = file;
	while (redir_p != endfile_p)
	{
		*file = *redir_p;
		redir_p++;
		file++;
	}
	*file = 0;
	file = ft_strtrim(tmp, " ");
	free(tmp);
	if (!file)
		return (0);
	return (file);
}

static void	take_com(char **str, char *redir_p, char *endfile_p)
{
	char	*com;

	*redir_p = 0;
	com = ft_strjoin(*str, endfile_p);
	free(*str);
	*str = com;
}

int	cut_file(char **str, char **file, int type)
{
	char	*redir_p;
	char	*endfile_p;

	if (type == R_RDR || type == DR_RDR)
		redir_p = ft_strchrq(*str, '>');
	else
		redir_p = ft_strchrq(*str, '<');
	endfile_p = redir_p;
	while (*endfile_p == '>' || *endfile_p == '<')
		endfile_p++;
	while (*endfile_p == ' ')
		endfile_p++;
	endfile_p = ft_strchrq(endfile_p, ' ');
	if (endfile_p == 0)
		endfile_p = redir_p + ft_strlen(redir_p);
	*file = take_file(redir_p, endfile_p);
	if (!*file)
		return (ERROR_MALLOC_CODE);
	take_com(str, redir_p, endfile_p);
	if (!*str)
	{
		free(*file);
		return (ERROR_MALLOC_CODE);
	}
	return (0);
}
