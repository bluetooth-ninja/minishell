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

	close(next->fd[0]);
	cur = com->content;
	res = 0;
	if (cur->fd[0])
		dup2(cur->fd[0], 0);
	dup2(next->fd[1], 1);
	exec_com = (t_list *)ft_calloc(1, sizeof(t_list));
	exec_com->content = com->content;
	res = do_command(0, com, env);
	if (cur->fd[0])
		close(cur->fd[0]);
	close(next->fd[1]);
	free(exec_com);
	exit(res);
}

static int	main_dl_rdr(t_list *com, char ***env, int res_fd[2], int fd[2])
{
	pid_t	pid;
	int		res;

	dup2(fd[0], 0);
	close(fd[1]);
	wait(NULL);
	res = 0;
	pid = fork();
	if (pid < 0)
		return (ERR_CODE);
	if (pid == 0)
	{
		dup2(res_fd[1], 1);
		res = do_command(0, com, env);
		close(res_fd[1]);
		close(fd[0]);
		exit(res);
	}
	waitpid(pid, &res, 0);
	close(fd[0]);
	return (WEXITSTATUS(res));
}

static int	double_left_redirect(char *file, t_list *com,
		char ***env, int res_fd[2])
{
	int		fd[2];
	pid_t	pid;
	int		res;

	if (pipe(fd) == -1)
		return (ERR_CODE);
	pid = fork();
	if (pid < 0)
		return (ERR_CODE);
	if (pid == 0)
		do_double_left_child(file, fd[0], fd[1]);
	else
		res = main_dl_rdr(com, env, res_fd, fd);
	return (res);
}

static void	pipe_double_left_redirect(t_list *com, char ***env, int fd[2])
{
	char		*file;
	t_command	*cur;
	int			res;

	close(fd[0]);
	cur = com->content;
	res = cut_file(&(cur->text), &file, DL_RDR, *env);
	if (res)
	{
		close(fd[1]);
		exit(res);
	}
	res = double_left_redirect(file, com, env, fd);
	free(file);
	close(fd[1]);
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
	if (cur->fd[0])
		close(cur->fd[0]);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
