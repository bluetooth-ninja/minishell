/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:13:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/25 00:56:28 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_type(char *str)
{
	int	i;
	int	type;

	type = 0;
	i = -1;
	while(str[++i])
	{
		if (str[i] == '>')
		{
			if (type < 0)
				return ('>');
			type++;
		}
		else if (str[i] == '<')
		{
			if (type > 0)
				return ('<');
			type--;
		}
		if (type && str[i] != '<' && str[i] != '>')
			break;
	}
	return (type);
}

int	cut_file(char **str, char **file)
{
	char	*tmp;
	char	*tmpp;
	int		len;
	char	*filep;

	tmp = *str;
	while (*tmp != '>' && *tmp != '<')
		tmp++;
	while (*tmp == '>' || *tmp == '<')
		tmp++;
	len = ft_strlen(*str);
	*file = substr_word(tmp, " \t|<>");
	tmp = *str;
	*str = (char *)malloc(sizeof(char) * (len - ft_strlen(*file)));
	tmpp = tmp;
	filep = *file;
	while (*tmp)
	{
		if (*tmp != *filep)
			**str = *tmp;
		else
			filep++;
		tmp++;
		(*str)++;
	}
	free(tmpp);
	return (0);
}

int	do_redir(char *str, char ***env)
{
	int		type;
	char	*file;

	(void)env;
	type = find_type(str);
	if (!type || type != '<' || type != '>')
	{
		//error
		return (-1);
	}
	cut_file(&str, &file);
	return (0);
}

int	is_builtin(char *line)
{
	if (!ft_memcmp(line, "echo", 5) || !ft_memcmp(line, "cd", 3) ||
		!ft_memcmp(line, "env", 4) || !ft_memcmp(line, "exit", 5) ||
		!ft_memcmp(line, "export", 7) || !ft_memcmp(line, "pwd", 4) ||
		!ft_memcmp(line, "unset", 6))
		return (1);
	return (0);
}

void	free_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

int	do_builtins(char **arr, char ***env)
{
	t_list	*words;
	int		i;
	int		res;

	i = 0;
	res = -1;
	words = 0;
	while (arr[++i])
		ft_lstadd_back(&words, ft_lstnew(arr[i]));
	if (!ft_memcmp(arr[0], "echo", 5))
		res = do_echo(words);
	else if (!ft_memcmp(arr[0], "cd", 3))
		res = do_cd(words, env);
	else if (!ft_memcmp(arr[0], "env", 4))
		res = do_env(*env);
	else if (!ft_memcmp(arr[0], "exit", 5))
		res = do_exit();
	else if (!ft_memcmp(arr[0], "export", 7))
		res = do_export(words, env);
	else if (!ft_memcmp(arr[0], "pwd", 4))
		res = do_pwd();
	else
		res = do_unset(words, env);
	free_list(words);
	return (res);
}

int	find_path(char **path, char **env)
{
	int			i;
	char	    *temp;
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

int	replace_variables(char **str, char **env, int is_q)
{
	int			i;
	int			len;
	char		*new_str;
	const char	*value;
	char		*name;
	char		*start;

	start = *str;
	i = -1;
	len = 0;
	new_str = ft_strchr(*str, '$');
	while (new_str[++i] && new_str[i] != ' ' && ((is_q == 1 &&
			new_str[i] != '\'') || (is_q == 2 && new_str[i] != '\"') || !is_q))
		len++;
	name = (char *)ft_calloc(len, sizeof(char));
	if (!name)
		return (-1);
	i = -1;
	while (new_str[++i + 1] && new_str[i + 1] != ' ' && ((is_q == 1 &&
			new_str[i + 1] != '\'') || (is_q == 2 && new_str[i + 1] != '\"') || !is_q))
		name[i] = new_str[i + 1];
	value = search_env_value(name, (const char **)env);
	free(name);
	name = new_str;
	new_str = ft_calloc(ft_strlen(*str) - len + ft_strlen(value) + 1, sizeof(char));
	i = 0;
	while (**str && *str != name)
	{
		new_str[i++] = **str;
		(*str)++;
	}
	while (*value)
		new_str[i++] = *value++;
	while (**str && **str != ' ' && ((is_q == 1 && **str != '\'') ||
			(is_q == 2 && **str != '\"') || !is_q))
		(*str)++;
	while (**str)
	{
		new_str[i++] = **str;
		(*str)++;
	}
	free(start);
	*str = new_str;
	return (0);
}

int	do_hast_quotes(char **str, char **env)
{
	int		is_q;
	char	*new_str;
	int		i;
	int		len;
	int		res;

	is_q = 0;
	i = -1;
	len = 0;
	res = 0;
	while ((*str)[++i] && !res)
	{
		if ((*str)[i] == '\'' && !is_q)
			is_q = 1;
		else if ((*str)[i] == '\"' && !is_q)
			is_q = 2;
		else if ((*str)[i] == '\"' && is_q == 2)
			is_q = 0;
		else if ((*str)[i] == '\'' && is_q == 1)
			is_q = 0;
		else if ((*str)[i] == '$' && is_q != 1)
		{
			res = replace_variables(str, env, is_q);
			i--;
		}
		else
			len++;
	}
	if (is_q)
		return (1);
	i = -1;
	new_str = (char *)calloc(len + 1, sizeof(char));
	if (!new_str)
		return (-1);
	res = 0;
	while ((*str)[++i] && res < len)
	{
		if ((*str)[i] == '\'' && !is_q)
			is_q = 1;
		else if ((*str)[i] == '\"' && !is_q)
			is_q = 2;
		else if ((*str)[i] == '\"' && is_q == 2)
			is_q = 0;
		else if ((*str)[i] == '\'' && is_q == 1)
			is_q = 0;
		else if ((*str)[i] == ' ' && is_q)
			new_str[res++] = 1;
		else
			new_str[res++] = (*str)[i];
	}
	free(*str);
	*str = new_str;
	return (0);
}

void	replace_spaces(char *str)
{
	while (*str)
	{
		if (*str == 1)
			*str = ' ';
		str++;
	}	
}

int	do_command(char *str, char ***env)
{
	char	**arr;
	int 	res;

	res = do_hast_quotes(&str, *env);
	if (ft_strchr(str, '>') || ft_strchr(str, '<'))
		return (do_redir(str, env));
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
		}
		wait(&res);
	}
	return (res);
}

void	do_proccess(t_command *cur, t_command *next, char ***env)
{
	int	res;

	res = 0;
	dup2(next->fd[1], 1);
	close(next->fd[1]);
    printf("LOL");
	if (cur->fd[0] != 0)
	{
		dup2(cur->fd[0], 0);
		close(cur->fd[0]);
	}
    printf("!!!");
	res = do_command(cur->text, env);
	exit(res);
}

int	do_pipes(t_command *cur, t_command *next, char ***env)
{
	int		res;
	//int		status;

	res = 0;
	if (pipe(next->fd) == -1)
		return (-1);
	if (fork() == 0)
    {
		printf("KEK");
        do_proccess(cur, next, env);
    }
	//не закрыли фд
	wait(NULL);
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
		if (line[i] == '\"' && !is_q)
			is_q = 2;
		if ((line[i] == '\'' && is_q == 1) || (line[i] == '\"' && is_q == 2))
			is_q = 0;
		if (line[i] == '|' && !is_q)
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
