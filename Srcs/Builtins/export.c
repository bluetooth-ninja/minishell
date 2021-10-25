/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:48 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 17:54:23 by wgaunt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_export(t_list *line_element, char ***env)
{
	while (line_element)
	{
		if (ft_strchr(line_element->content, '='))
			change_env_var(line_element->content, env);
		line_element = line_element->next;
	}
	return (0);
}
