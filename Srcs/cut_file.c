/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:11:36 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/03 00:38:39 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_for_rita(char **file, int res)
{
	if (res == -2 || res == -3)
		free(*file);
	return (res);
}

static int	take_file(char **file, char *redir_p, char *endfile_p, char **env)
{
	char	*tmp;
	int		res;

	while (*redir_p == '<' || *redir_p == '>')
		redir_p++;
	while (*redir_p == ' ')
		redir_p++;
	*file = (char *)ft_calloc(endfile_p - redir_p + 1, sizeof(char));
	if (!(*file))
		return (ERR_CODE);
	tmp = *file;
	while (redir_p != endfile_p)
	{
		*tmp = *redir_p;
		redir_p++;
		tmp++;
	}
	*tmp = 0;
	tmp = *file;
	*file = ft_strtrim(tmp, " ");
	free(tmp);
	if (!(*file))
		return (ERR_CODE);
	res = do_hast_quotes(file, env, 1);
	return (res);
}

static void	take_com(char **str, char *redir_p, char *endfile_p)
{
	char	*com;

	*redir_p = 0;
	com = ft_strjoin(*str, endfile_p);
	free(*str);
	*str = com;
}

static char	*find_end(char *start)
{
	int	is_q;

	is_q = 0;
	while (*start == '>' || *start == '<')
		start++;
	while (*start == ' ')
		start++;
	while (*start && *start != '<' && *start != '>' && (*start != ' '
			|| (*start == ' ' && is_q)))
	{
		if (!is_q && *start == '\'')
			is_q = 1;
		else if (!is_q && *start == '\"')
			is_q = 2;
		else if ((is_q == 2 && *start == '\"')
			|| (is_q == 1 && *start == '\''))
			is_q = 0;
		start++;
	}
	return (start);
}

int	cut_file(char **str, char **file, int type, char **env)
{
	char	*redir_p;
	char	*endfile_p;
	int		res;
	char	*tmp;

	if (type == R_RDR || type == DR_RDR)
		redir_p = ft_strchrq(*str, '>');
	else
		redir_p = ft_strchrq(*str, '<');
	endfile_p = find_end(redir_p);
	if (endfile_p == 0)
		endfile_p = redir_p + ft_strlen(redir_p);
	res = take_file(file, redir_p, endfile_p, env);
	tmp = *file - 1;
	while (*(++tmp))
		if (*tmp == 1)
			*tmp = ' ';
	if (res)
		return (quotes_for_rita(file, res));
	take_com(str, redir_p, endfile_p);
	if (!*str)
		free(*file);
	if (!*str)
		return (ERR_CODE);
	return (0);
}
