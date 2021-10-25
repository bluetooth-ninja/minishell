/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <vlucilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:43 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 16:57:20 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(t_list **list)
{
	t_list	*line_element;

	line_element = *list;
	if (line_element->next)
	{
		if (!ft_strncmp((char *)line_element->content, "-n", 3))
		{
			*list = line_element->next;
			return (0);
		}
	}
	return (1);
}

void	print_n(int is_nl)
{
	if (is_nl)
		printf("\n");
}

int	do_echo(t_list *line_element)
{
	int		is_nl;
	char	*text;

	is_nl = 1;
	if (line_element)
		is_nl = check_option(&line_element);
	text = (char *)1;
	while (text && line_element)
	{
		text = line_element->content;
		if (!ft_strncmp(text, "-n", 2) && text[2] == 0)
			line_element = line_element->next;
		else
			text = 0;
	}
	while (line_element)
	{
		if (text)
			printf(" ");
		text = line_element->content;
		printf("%s", text);
		line_element = line_element->next;
	}
	print_n(is_nl);
	return (0);
}
