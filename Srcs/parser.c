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

int	find_path(char **path, char **env)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

	temp = (char *)search_env_value("PATH", (const char **)env);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", *path);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &s) == 0)
		{
			free(*path);
			*path = new_path;
			free_array(paths);
			return (0);
		}
		free(new_path);
	}
	free_array(paths);
	return (1);
}

int	do_command(char *str, char ***env)
{
	char	**arr;
	int 	res;

	if (ft_strchrq(str, '>') || ft_strchrq(str, '<'))
		return (parse_redir(str, env));
	res = do_hast_quotes(&str, *env);
	if (res)
		return (res);
	arr = space_split(str);
	if (!arr)
		return (-1);
	if (is_builtin(arr[0]))
		res = do_builtins(arr, env);
	else
	{
		if (fork() == 0)
		{
			res = find_path(&arr[0], *env);
			res = execve(arr[0], arr, *env);
			exit(res);
		}
		wait(&res);
	}
	return (res);
}

static int	add_commands(t_list **commands, char *com_line, int com_len)
{
	t_list		*new_el;
	char		*trim_com;
	char		*tmp;
	t_command	*new_com;

	trim_com = (char *)ft_calloc(com_len + 1, sizeof(char));
	if (!trim_com)
		return (-1);
	ft_strlcpy(trim_com, com_line, com_len + 1);
	tmp = ft_strtrim(trim_com, "\t ");
	free(trim_com);
	if (!tmp)
		return (-1);
	trim_com = tmp;
	new_com = (t_command *)malloc(sizeof(t_command));
	if (!new_com)
	{
		free(trim_com);
		return (-1);
	}
	new_com->text = trim_com;
	new_el = ft_lstnew(new_com);
	if (!new_el)
	{
		free(trim_com);
		free(new_com);
		return (-1);
	}
	ft_lstadd_back(commands, new_el);
	return (0);
}

static t_list	*pipe_split(char *line)
{
	t_list	*commands;
	int		i;
	int		is_q;
	int		start;

	start = 0;
	i = 0;
	commands = 0;
	is_q = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !is_q)
			is_q = 1;
		else if (line[i] == '\"' && !is_q)
			is_q = 2;
		else if ((line[i] == '\'' && is_q == 1) || (line[i] == '\"' && is_q == 2))
			is_q = 0;
		else if (line[i] == '|' && !is_q)
		{
			add_commands(&commands, &line[start], i - start);
			start = i + 1;
		}
		i++;
	}
	add_commands(&commands, &line[start], i - start);
	return (commands);
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
		return (1);
	while (commands)
	{
		if (!commands->next)
			res = do_command(((t_command *)commands->content)->text, env);
		else
			res = do_pipes(commands->content, commands->next->content, env);
		commands = commands->next;
	}
	return (res);
}
