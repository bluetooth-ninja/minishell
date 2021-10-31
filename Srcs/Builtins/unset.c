/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:53 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 16:50:57 by vlucilla         ###   ########.fr       */
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
				return (ERROR_MALLOC_CODE);
		}
		else
		{
			ft_putstr_fd("minishell: export: «", 2);
			ft_putstr_fd(line_element->content, 2);
			ft_putendl_fd("»: wrong input", 2);
		}
		line_element = line_element->next;
	}
	return (res);
}
