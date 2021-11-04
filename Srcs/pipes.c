/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:27:26 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/02 01:04:18 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_proccess(t_list *com, t_command *next, char ***env)
{
	int			res;
	t_command	*cur;
	t_list		*exec_com;

	cur = com->content;
	res = 0;
	if (cur->fd[0])
		dup2(cur->fd[0], 0);
	dup2(next->fd[1], 1);
	exec_com = (t_list *)ft_calloc(1, sizeof(t_list));
	exec_com->content = com->content;
	res = do_command(0, com, env);
	free(exec_com);
	exit(res);
}

int	do_pipes(t_list *com, t_command *next, char ***env)
{
	pid_t	pid;
	int		status;

	if (pipe(next->fd) == -1)
		return (ERR_CODE);
	status = 0;
	pid = fork();
	if (pid < 0)
		return (ERR_CODE);
	if (pid == 0)
	{
		do_proccess(com, next, env);
		exit(0);
	}
	close(next->fd[1]);
	waitpid(pid, &status, 0);
	g_sh_exit = WEXITSTATUS(status);
	return (status);
}

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
	{
		free(trim_com);
		return (ERR_CODE);
	}
	new_com->text = trim_com;
	new_el = ft_lstnew(new_com);
	if (!new_el)
	{
		free(trim_com);
		free(new_com);
		return (ERR_CODE);
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
