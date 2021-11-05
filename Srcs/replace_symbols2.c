/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_symbols2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 00:53:37 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/03 00:39:53 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_value(char *str, char **env, int *len)
{
	char	*n_str;
	char	*name;
	int		i;
	char	*value;

	i = 1;
	*len = 2;
	n_str = ft_strchr(str, '$');
	if (!ft_isalpha(str[1]) && str[1] != '_' && str[1] == '?')
		return (search_env_value("?", (const char **)env));
	else if (!ft_isalpha(str[1]) && str[1] != '_')
		return (ft_strdup(""));
	while (n_str[++i] && (ft_isalnum(n_str[i]) || n_str[i] == '_'))
		(*len)++;
	name = (char *)ft_calloc(*len, sizeof(char));
	if (!name)
		return (0);
	i = -1;
	while (++i + 1 < *len)
		name[i] = n_str[i + 1];
	value = search_env_value(name, (const char **)env);
	free(name);
	return (value);
}

char	*change_name_to_value(char **str, char *new_str, char *value, int j)
{
	char	*name;
	int		i;
	char	*t_str;

	t_str = *str - 1;
	name = ft_strchr(&t_str[j], '$');
	i = 0;
	while (*(++t_str) && t_str != name)
		new_str[i++] = *t_str;
	while (*value)
		new_str[i++] = *value++;
	t_str++;
	if (ft_isalpha(*t_str) || *t_str == '_')
	{
		t_str++;
		while (*t_str && (ft_isalnum(*t_str) || *t_str == '_'))
			t_str++;
	}
	else if (*t_str)
		t_str++;
	t_str--;
	while (*(++t_str))
		new_str[i++] = *t_str;
	return (new_str);
}
