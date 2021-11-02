/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:23:52 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/02 22:25:46 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sh_exit = 0;

void	signal_handler(int signum)
{
	pid_t	pid;
	int		res;

	pid = waitpid(-1, &res, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
	{
		if (pid != -1)
			write(1, "Quit\n", 5);
	}
}

static int	read_lines(char ***env)
{
	char	*line;
	int		res;

	res = 0;
	while (res != ERR_CODE)
	{
		line = readline("\x1b[1;30;43m♡❤(„• ᴗ •„)❤♡:\x1b[0m ");
		if (line == NULL)
			exit(g_sh_exit);
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			res = parse_com(line, env);
		}
		free(line);
	}
	return (res);
}

int	main(int ac, char **av, char **penv)
{
	int		res;
	char	***env;

	env = (char ***)malloc(sizeof(char **));
	if (!env)
	{
		ft_putendl_fd(ERROR_MALLOC_MSG, 2);
		return (ERR_CODE);
	}
	*env = 0;
	res = env_cpy(env, penv);
	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (!res)
		res = read_lines(env);
	if (*env)
		free_array(*env);
	free(env);
	ft_putendl_fd(ERROR_MALLOC_MSG, 2);
	return (ERR_CODE);
}
