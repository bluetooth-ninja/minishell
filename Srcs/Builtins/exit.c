/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/06 17:55:22 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit(char *str, int err, char **arr)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd(str, 2);
	if (err == 1)
		g_sh_exit = 1;
	if (err == 2)
		g_sh_exit = 2;
	free_array(arr);
	exit(g_sh_exit);
}

static int	is_digits(char *str)
{
	if (str[0] == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static void	free_exit(t_list *words, t_list *com, char ***env)
{
	free_list(words);
	ft_lstclear(&com, t_command_clear);
	free_array(*env);
	free(env);
}

int	do_exit(char **arr, t_list *words, t_list *com, char ***env)
{
	int	nb;

	nb = 1;
	while (arr[nb])
		nb++;
	free_exit(words, com, env);
	if (nb == 1)
		ft_exit(NULL, 0, arr);
	if (nb == 2 && is_digits(arr[1]))
	{
		if (ft_atoi(arr[1]) > 256)
			g_sh_exit = ft_atoi(arr[1]) % 256;
		else
			g_sh_exit = ft_atoi(arr[1]);
		ft_exit(NULL, 0, arr);
	}
	if (nb >= 2 && !is_digits(arr[1]))
		ft_exit("minishell: exit: numeric argument required", 2, arr);
	if (nb > 2 && (is_digits(arr[1])))
		ft_exit("minishell: exit: too many arguments", 1, arr);
	return (0);
}
