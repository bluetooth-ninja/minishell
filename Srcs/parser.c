/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:13:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/31 03:57:55 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execution(char **arr, char **env)
{
	int		res;

	res = find_path(arr, env);
	if (res == ERROR_MALLOC_CODE)
		exit(res);
	res = execve(arr[0], arr, env);
	if (res == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arr[0], 2);
		ft_putendl_fd(": command not found", 2);
		g_sh_exit = 127;
	}
	exit(res);
}

int	do_command(t_list *command, char ***env)
{
	char	**arr;
	int		res;
	char	**str;

	str = &(((t_command *)(command->content))->text);
	if (ft_strchrq(*str, '>') || ft_strchrq(*str, '<'))
		return (parse_redir(command, env));
	res = do_hast_quotes(str, *env);
	if (res == ERROR_MALLOC_CODE)
		return (ERROR_MALLOC_CODE);
	if (res == -2)
		return (0);
	arr = space_split(*str);
	if (!arr)
		return (ERROR_MALLOC_CODE);
	if (arr[0] && is_builtin(arr[0]))
		res = do_builtins(arr, env, command);
	else if (arr[0])
	{
		if (fork() == 0)
			execution(arr, *env);
		wait(&res);
	}
	free_array(arr);
	return (0);
}

static int	ifempty(t_list **commands)
{
	t_command	*com;
	t_list		*command;
	int			is_err;

	is_err = 0;
	command = *commands;
	while (command && !is_err)
	{
		com = command->content;
		if (*(com->text) == 0)
			is_err = 1;
		command = command->next;
	}
	if (is_err)
	{
		ft_lstclear(commands, t_command_clear);
		ft_putendl_fd(ERROR_EMPTYPIPE_MSG, 2);
		return (1);
	}
	return (0);
}

int	parse_com(char *line, char ***env)
{
	int		res;
	t_list	*commands;
	t_list	*tmp;

	while (*line == ' ')
		line++;
	if (!(*line))
		return (0);
	res = 0;
	commands = 0;
	commands = pipe_split(line);
	if (!commands)
		return (ERROR_MALLOC_CODE);
	tmp = commands;
	if (ifempty(&commands))
		return (0);
	while (commands)
	{
		if (!commands->next)
			res = do_command(commands, env);
		else
			res = do_pipes(commands->content, commands->next->content, env);
		commands = commands->next;
	}
	ft_lstclear(&tmp, t_command_clear);
	return (res);
}
