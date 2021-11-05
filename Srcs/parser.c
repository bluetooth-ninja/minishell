/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:13:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/05 04:16:20 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_commands(t_list **commands, char *com_line, int com_len)
{
	t_list		*new_el;
	char		*trim_com;
	char		*tmp;
	t_command	*new_com;

	trim_com = (char *)ft_calloc(com_len + 1, sizeof(char));
	if (!trim_com)
		return (ERR_CODE);
	ft_strlcpy(trim_com, com_line, com_len + 1);
	tmp = ft_strtrim(trim_com, "\t ");
	free(trim_com);
	if (!tmp)
		return (ERR_CODE);
	trim_com = tmp;
	new_com = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new_com)
		return (pars_err(trim_com, new_com));
	new_com->text = trim_com;
	new_el = ft_lstnew(new_com);
	if (!new_el)
		return (pars_err(trim_com, new_com));
	ft_lstadd_back(commands, new_el);
	return (0);
}

t_list	*pipe_split(char *line)
{
	t_list	*commands;
	int		i;
	int		is_q;
	int		start;

	start = 0;
	i = -1;
	commands = 0;
	is_q = 0;
	while (line[++i])
	{
		if ((line[i] == '\'' && is_q == 1) || (line[i] == '\"' && is_q == 2))
			is_q = 0;
		else if (line[i] == '\'' && !is_q)
			is_q = 1;
		else if (line[i] == '\"' && !is_q)
			is_q = 2;
		else if (line[i] == '|' && !is_q)
		{
			add_commands(&commands, &line[start], i - start);
			start = i + 1;
		}
	}
	add_commands(&commands, &line[start], i - start);
	return (commands);
}

static int	ifempty(t_list **commands)
{
	t_command	*com;
	t_list		*command;
	int			is_err;

	is_err = 0;
	command = *commands;
	while (command && !is_err)
	{
		com = command->content;
		if (*(com->text) == 0)
			is_err = 1;
		command = command->next;
	}
	if (is_err)
	{
		ft_lstclear(commands, t_command_clear);
		ft_putendl_fd(ERROR_EMPTYPIPE_MSG, 2);
		g_sh_exit = 2;
		return (1);
	}
	return (0);
}

static int	do_commands(t_list *commands, char ***env)
{
	int	res;
	int	is_p;

	is_p = 0;
	res = 0;
	while (commands)
	{
		if (!commands->next)
			res = do_command(is_p, commands, env);
		else
		{
			res = do_pipes(commands, commands->next->content, env);
			is_p = 1;
		}
		commands = commands->next;
	}
	return (res);
}

int	parse_com(char *line, char ***env)
{
	int		res;
	t_list	*commands;
	t_list	*tmp;

	while (*line == ' ')
		line++;
	if (!(*line))
		return (0);
	res = 0;
	commands = 0;
	commands = pipe_split(line);
	if (!commands)
		return (ERR_CODE);
	tmp = commands;
	if (ifempty(&commands))
		return (0);
	res = do_commands(commands, env);
	ft_lstclear(&tmp, t_command_clear);
	return (res);
}
