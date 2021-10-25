/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:27:26 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/26 00:40:03 by vlucilla         ###   ########.fr       */
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
	//int		res;
	int		status;

	//res = 0;
	if (pipe(next->fd) == -1)
		return (-1);
	if (fork() == 0)
        do_proccess(cur, next, env);
	//не закрыли фд
	wait(&status);
	return (0);
}