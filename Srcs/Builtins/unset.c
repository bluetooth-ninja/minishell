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
	int	i;
	int	res;

	res = 0;
	while (line_element)
	{
		i = 0;
		while (((char *)(line_element->content))[i] == '_' ||
				ft_isalnum(((char *)(line_element->content))[i]))
			i++;
		if ((unsigned int)i != ft_strlen(line_element->content))
			res = 1;
		else if (remove_var(line_element->content, env))
			return (ERROR_MALLOC_CODE);
		line_element = line_element->next;
	}
	return (res);
}
