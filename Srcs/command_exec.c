/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 03:41:21 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/05 04:23:07 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_execve(char **arr, char **env)
{
	pid_t	pid;
	int		res;
	int		status;

	res = 0;
	pid = fork();
	if (pid == -1)
		return (ERR_CODE);
	if (pid == 0)
	{
		if (!ft_strchr(arr[0], '/'))
			res = find_path(arr, env);
		if (res == ERR_CODE)
			exit(ERR_CODE);
		res = execve(arr[0], arr, env);
		if (res == -1)
			execve_err(arr[0]);
		exit(res);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	do_com(t_list *command, char ***env)
{
	char	**arr;
	int		res;
	char	**str;

	str = &(((t_command *)(command->content))->text);
	if (ft_strchrq(*str, '>') || ft_strchrq(*str, '<'))
		return (parse_redir(command, env));
	res = do_hast_quotes(str, *env, 0);
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

int	do_command(int is_p, t_list *command, char ***env)
{
	pid_t	pid;
	int		status;
	int		res;

	if (is_p)
	{
		pid = fork();
		if (pid < 0)
			return (ERR_CODE);
		if (pid == 0)
		{
			if (find_type(((t_command *)(command->content))->text) != DL_RDR)
				dup2(((t_command *)(command->content))->fd[0], 0);
			res = do_com(command, env);
			close(((t_command *)(command->content))->fd[0]);
			exit(res);
		}
		close(((t_command *)(command->content))->fd[0]);
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	else
		status = do_com(command, env);
	g_sh_exit = status;
	return (status);
}
