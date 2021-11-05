/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:45 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/06 00:51:24 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(char **env, char **arr)
{
	if (!arr || !arr[1])
	{
		while (*env != 0)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}
	else
	{
		ft_putendl_fd("minishell: env: with no options or arguments", 2);
		g_sh_exit = 1;
		return (1);
	}
}
