/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:27:26 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/31 04:00:41 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_proccess(t_command *cur, t_command *next, char ***env)
{
	int	res;

	res = 0;
	dup2(next->fd[1], 1);
	close(next->fd[1]);
	if (cur->fd[0] != 0)
	{
		dup2(cur->fd[0], 0);
		close(cur->fd[0]);
	}
	res = do_command(cur->text, env);
	exit(res);
}

int	do_pipes(t_command *cur, t_command *next, char ***env)
{
	int		status;

	if (pipe(next->fd) == -1)
		return (-1);
	if (fork() == 0)
		do_proccess(cur, next, env);
	wait(&status);
	return (0);
}

static int	add_commands(t_list **commands, char *com_line, int com_len)
{
	t_list		*new_el;
	char		*trim_com;
	char		*tmp;
	t_command	*new_com;

	trim_com = (char *)ft_calloc(com_len + 1, sizeof(char));
	if (!trim_com)
		return (ERROR_MALLOC_CODE);
	ft_strlcpy(trim_com, com_line, com_len + 1);
	tmp = ft_strtrim(trim_com, "\t ");
	free(trim_com);
	if (!tmp)
		return (ERROR_MALLOC_CODE);
	trim_com = tmp;
	new_com = (t_command *)malloc(sizeof(t_command));
	if (!new_com)
	{
		free(trim_com);
		return (ERROR_MALLOC_CODE);
	}
	new_com->text = trim_com;
	new_el = ft_lstnew(new_com);
	if (!new_el)
	{
		free(trim_com);
		free(new_com);
		return (ERROR_MALLOC_CODE);
	}
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
	i = 0;
	commands = 0;
	is_q = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !is_q)
			is_q = 1;
		else if (line[i] == '\"' && !is_q)
			is_q = 2;
		else if ((line[i] == '\'' && is_q == 1) || (line[i] == '\"' && is_q == 2))
			is_q = 0;
		else if (line[i] == '|' && !is_q)
		{
			add_commands(&commands, &line[start], i - start);
			start = i + 1;
		}
		i++;
	}
	add_commands(&commands, &line[start], i - start);
	return (commands);
}
