/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 03:33:52 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/05 04:32:36 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_double_left_child(char *file, int fd0, int fd)
{
	int		len;
	char	*line;

	line = NULL;
	len = ft_strlen(file);
	close(fd0);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putstr_fd("minishell: warning: ", 2);
			ft_putendl_fd("here-document delimited by end-of-file", 2);
			break ;
		}
		if (!ft_strncmp(line, file, len + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

int	double_left_redirect(char *file, t_list *com, char ***env, int fd[2])
{
	int		res;
	pid_t	pid;

	res = 0;
	pid = fork();
	if (pid < 0)
		return (ERR_CODE);
	if (pid == 0)
		do_double_left_child(file, fd[0], fd[1]);
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(NULL);
		res = do_command(0, com, env);
		close(fd[0]);
	}
	return (res);
}

int	do_double_left_redirect(char *file, t_list *com, char ***env)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ERR_CODE);
	return (double_left_redirect(file, com, env, fd));
}
