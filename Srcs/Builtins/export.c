/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:48 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/06 00:39:34 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export(t_list *line_element, char ***env)
{
	int	res;

	while (line_element)
	{
		if (is_correct_var(line_element->content, 1))
		{
			if (ft_strchr(line_element->content, '='))
			{
				res = change_env_var(line_element->content, env);
				if (res == ERR_CODE)
					return (res);
			}
		}
		else
		{
			ft_putstr_fd("minishell: export: «", 2);
			ft_putstr_fd(line_element->content, 2);
			ft_putendl_fd("»: wrong input", 2);
			g_sh_exit = 1;
			return (1);
		}
		line_element = line_element->next;
	}
	return (0);
}

int	do_export(t_list *line_element, char ***env)
{
	int	res;

	if (line_element)
		res = export(line_element, env);
	else
		res = do_env(*env, NULL);
	return (res);
}
