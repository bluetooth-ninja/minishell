/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 03:33:52 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/30 16:52:44 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_double_left_child(char *file, int fd)
{
	int		len;
	char	*line;

	line = NULL;
	len = ft_strlen(file);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, file, len + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

int	do_double_left_redirect(char *file, char *str, char ***env)
{
	int	res;
	int	fd[2];

	pipe(fd);
	res = 0;
	if (fork() == 0)
	{
		close(fd[0]);
		do_double_left_child(file, fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(NULL);
		res = do_command(str, env);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	return (res);
}
