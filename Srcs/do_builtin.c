/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:34:55 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/06 00:36:36 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *line)
{
	if (!ft_memcmp(line, "echo", 5) || !ft_memcmp(line, "cd", 3)
		|| !ft_memcmp(line, "env", 4) || !ft_memcmp(line, "exit", 5)
		|| !ft_memcmp(line, "export", 7) || !ft_memcmp(line, "pwd", 4)
		|| !ft_memcmp(line, "unset", 6))
		return (1);
	return (0);
}

int	do_builtins(char **arr, char ***env, t_list *com)
{
	t_list	*words;
	int		i;

	i = 0;
	words = 0;
	while (arr[++i])
		ft_lstadd_back(&words, ft_lstnew(arr[i]));
	if (!ft_memcmp(arr[0], "echo", 5))
		i = do_echo(words);
	else if (!ft_memcmp(arr[0], "cd", 3))
		i = do_cd(words, env);
	else if (!ft_memcmp(arr[0], "env", 4))
		i = do_env(*env, arr);
	else if (!ft_memcmp(arr[0], "exit", 5))
		i = do_exit(arr, words, com, env);
	else if (!ft_memcmp(arr[0], "export", 7))
		i = do_export(words, env);
	else if (!ft_memcmp(arr[0], "pwd", 4))
		i = do_pwd();
	else
		i = do_unset(words, env);
	free_list(words);
	return (i);
}
