/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <vlucilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:13:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/26 19:09:00 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_path(char **path, char *dir)
{
	char		*temp;
	char		*new_path;
	struct stat	s;

	temp = ft_strjoin("/", *path);
	if (!temp)
		return (ERROR_MALLOC_CODE);
	new_path = ft_strjoin(dir, temp);
	free(temp);
	if (!new_path)
		return (ERROR_MALLOC_CODE);
	if (stat(new_path, &s) == 0)
	{
		free(*path);
		*path = new_path;
		return (1);
	}
	free(new_path);
	return (0);
}

static int	find_path(char **path, char **env)
{
	int		i;
	char	*temp;
	char	**paths;
	int		is_find;

	is_find = 0;
	temp = (char *)search_env_value("PATH", (const char **)env);
	if (!temp)
		return (ERROR_MALLOC_CODE);
	paths = ft_split(temp, ':');
	free(temp);
	if (!paths)
		return (ERROR_MALLOC_CODE);
	i = -1;
	while (paths[++i] && !is_find)
		is_find = try_path(path, paths[i]);
	free_array(paths);
	return (is_find);
}

static void	execution(char **arr, char **env)
{
	int		res;
	char	*err;

	res = find_path(arr, env);
	if (res == ERROR_MALLOC_CODE)
		exit(res);
	execve(arr[0], arr, env);
	err = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(err, 2);
	exit(0);
}

int	do_command(char *str, char ***env)
{
	char	**arr;
	int 	res;

	if (ft_strchrq(str, '>') || ft_strchrq(str, '<'))
		return (parse_redir(str, env));
	res = do_hast_quotes(&str, *env);
	if (res == ERROR_MALLOC_CODE)
		return (ERROR_MALLOC_CODE);
	arr = space_split(str);
	if (!arr)
		return (ERROR_MALLOC_CODE);
	if (is_builtin(arr[0]))
		res = do_builtins(arr, env);
	else
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

	while (*line == ' ')
		line++;
	if (!(*line))
		return (0);
	res = 0;
	commands = 0;
	commands = pipe_split(line);
	if (!commands)
		return (ERROR_MALLOC_CODE);
	if (ifempty(&commands))
		return (0);
	while (commands)
	{
		if (!commands->next)
			res = do_command(((t_command *)commands->content)->text, env);
		else
			res = do_pipes(commands->content, commands->next->content, env);
		commands = commands->next;
	}
	ft_lstclear(&commands, t_command_clear);
	return (res);
}
