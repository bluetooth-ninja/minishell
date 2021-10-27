/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:23:52 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/28 00:29:39 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sh_exit = 0;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **penv)
{
	char	*line;
	int		res;
	char	***env;

	line = NULL;
	env = (char ***)malloc(sizeof(char **));
	if (env_cpy(env, penv))
		return (0);				//error
	res = 0;
	(void)av;
	(void)ac;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline("\x1b[1;30;43m♡❤(„• ᴗ •„)❤♡:\x1b[0m ");
		if (line == NULL)
			exit(sh_exit);
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			res = parse_com(line, env);
		}
		free(line);
	}
	return (res);
}
