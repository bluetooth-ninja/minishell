/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:13:52 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/06 14:45:34 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_right_redirect(char *file, t_list *com, char ***env)
{
	int	fd;
	int	res;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_sh_exit = 1;
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	res = do_command(0, com, env);
	return (res);
}

static int	do_left_redirect(char *file, t_list *com, char ***env)
{
	int	fd;
	int	res;

	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_sh_exit = 1;
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	res = do_command(0, com, env);
	return (res);
}

static int	do_double_right_redirect(char *file, t_list *com, char ***env)
{
	int	fd;
	int	res;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_sh_exit = 1;
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	res = do_command(0, com, env);
	return (res);
}

int	do_redirects(int type, char *file, t_list *com, char ***env)
{
	int		res;
	pid_t	pid;

	res = 0;
	pid = fork();
	if (pid == -1)
		return (ERR_CODE);
	if (pid == 0)
	{
		if (type == R_RDR)
			res = do_right_redirect(file, com, env);
		else if (type == L_RDR)
			res = do_left_redirect(file, com, env);
		else if (type == DR_RDR)
			res = do_double_right_redirect(file, com, env);
		else if (type == DL_RDR)
			res = do_double_left_redirect(file, com, env);
		exit(res);
	}
	waitpid(pid, &res, 0);
	g_sh_exit = WEXITSTATUS(res);
	return (WEXITSTATUS(res));
}
