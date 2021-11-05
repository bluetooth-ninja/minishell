/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:27:26 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/05 04:23:48 by vlucilla         ###   ########.fr       */
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

static void	pipe_double_left_redirect(t_list *com, char ***env, int fd[2])
{
	char		*file;
	t_command	*cur;
	int			res;

	cur = com->content;
	res = cut_file(&(cur->text), &file, DL_RDR, *env);
	if (res)
		exit(res);
	res = double_left_redirect(file, com, env, fd);
	free(file);
	exit(res);
}

int	do_pipes(t_list *com, t_command *next, char ***env)
{
	pid_t		pid;
	int			status;
	t_command	*cur;

	cur = com->content;
	if (pipe(next->fd) == -1)
		return (ERR_CODE);
	status = 0;
	pid = fork();
	if (pid < 0)
		return (ERR_CODE);
	if (pid == 0)
	{
		if (find_type(cur->text) == DL_RDR)
			pipe_double_left_redirect(com, env, next->fd);
		else
			do_proccess(com, next, env);
	}
	close(next->fd[1]);
	waitpid(pid, &status, 0);
	return (status);
}
