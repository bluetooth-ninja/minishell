/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:13:52 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/26 00:45:16 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int do_right_redirect(char *file, char *str, char ***env)
{
	int fd;
	int res;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		printf("%s", "error\n");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	res = do_command(str, env);
	return (res);
}

static int do_left_redirect(char *file, char *str, char ***env)
{
	int fd;
	int res;

	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		printf("%s", "error\n");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	res = do_command(str, env);
	return (res);
}

static int do_double_right_redirect(char *file, char *str, char ***env)
{
	int fd;
	int res;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		printf("%s", "error\n");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	res = do_command(str, env);
	return (res);
}

int do_double_left_redirect(char *file, char *str, char ***env)
{
	(void)file;
	(void)str;
	(void)env;
	return (0);
}

int do_redirects(int type, char *file, char *str, char ***env)
{
	int	res;
	int	status;
    
	res = 0;
    if (fork() == 0)
	{
		if (type == R_RDR)
			res = do_right_redirect(file, str, env);
		else if (type == L_RDR)
			res = do_left_redirect(file, str, env);
		else if (type == DR_RDR)
			res = do_double_right_redirect(file, str, env);
		else if (type == DL_RDR)
			res = do_double_left_redirect(file, str, env);
		exit(res);
	}
	wait(&status);
	sh_exit = status / 256;
    return (res);
}
