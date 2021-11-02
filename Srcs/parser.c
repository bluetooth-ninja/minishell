/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:13:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/03 00:17:41 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_execve(char **arr, char **env)
{
	pid_t	pid;
	int		res;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ERR_CODE);
	if (pid == 0)
	{
		res = find_path(arr, env);
		if (res == ERR_CODE)
			exit(ERR_CODE);
		res = execve(arr[0], arr, env);
		if (res == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arr[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		exit(res);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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
	if (res)
	{
		if (res == ERR_CODE)
			return (ERR_CODE);
		else
			return (2);
	}
	arr = space_split(*str);
	if (!arr)
		return (ERR_CODE);
	if (arr[0] && is_builtin(arr[0]))
		g_sh_exit = do_builtins(arr, env, command);
	else if (arr[0])
		g_sh_exit = command_execve(arr, *env);
	free_array(arr);
	return (g_sh_exit);
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
		g_sh_exit = 2;
		return (1);
	}
	return (0);
}

static int	do_commands(t_list *commands, char ***env)
{
	int	res;

	res = 0;
	while (commands)
	{
		if (!commands->next)
			res = do_command(commands, env);
		else
			res = do_pipes(commands->content, commands->next->content, env);
		commands = commands->next;
	}
	return (res);
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
		return (ERR_CODE);
	tmp = commands;
	if (ifempty(&commands))
		return (0);
	res = do_commands(commands, env);
	ft_lstclear(&tmp, t_command_clear);
	return (res);
}
