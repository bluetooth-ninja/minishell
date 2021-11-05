/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 03:33:52 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/05 21:53:16 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_double_left_child(char *file, int fd0, int fd)
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

int	do_double_left_redirect(char *file, t_list *com, char ***env)
{
	int		res;
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ERR_CODE);
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
		exit(res);
	}
	return (res);
}
