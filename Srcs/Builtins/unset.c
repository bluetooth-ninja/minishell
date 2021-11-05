/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:53 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/06 01:11:13 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_unset(t_list *line_element, char ***env)
{
	int	res;

	res = 0;
	while (line_element)
	{
		if (is_correct_var(line_element->content, 0))
		{
			if (remove_var(line_element->content, env))
				return (ERR_CODE);
		}
		else
		{
			ft_putstr_fd("minishell: unset: «", 2);
			ft_putstr_fd(line_element->content, 2);
			ft_putendl_fd("»: wrong input", 2);
			g_sh_exit = 1;
			return (1);
		}
		line_element = line_element->next;
	}
	return (res);
}
