/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_symbols2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 00:53:37 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/29 00:55:16 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_value(char *str, char **env, int is_q, int *len)
{
	char	*n_str;
	char	*name;
	int		i;
	char	*value;

	i = -1;
	*len = 0;
	n_str = ft_strchr(str, '$');
	while (n_str[++i] && n_str[i] != ' ' && ((is_q == 2 && n_str[i] != '\"') ||
			(!is_q && n_str[i] != '\'' && n_str[i] != '\"')))
		(*len)++;
	name = (char *)ft_calloc(*len, sizeof(char));
	if (!name)
		return (0);
	i = -1;
	while (n_str[++i + 1] && n_str[i + 1] != ' ' && ((is_q == 2 &&
			n_str[i + 1] != '\"') || (!is_q && n_str[i + 1] != '\'' &&
			n_str[i + 1] != '\"')))
		name[i] = n_str[i + 1];
	value = search_env_value(name, (const char **)env);
	free(name);
	return (value);
}

char	*change_name_to_value(char **str, char *new_str, char *value, int is_q)
{
	char	*name;
	int		i;

	name = ft_strchr(*str, '$');
	i = 0;
	while (**str && *str != name)
	{
		new_str[i++] = **str;
		(*str)++;
	}
	while (*value)
		new_str[i++] = *value++;
	while (**str && **str != ' ' && ((is_q == 2 && **str != '\"') ||
			(!is_q && **str != '\'' && **str != '\"')))
		(*str)++;
	while (**str)
	{
		new_str[i++] = **str;
		(*str)++;
	}
	return (new_str);
}
