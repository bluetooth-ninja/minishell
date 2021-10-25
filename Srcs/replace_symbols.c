/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:33:15 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/26 00:33:58 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_variables(char **str, char **env, int is_q)
{
	int			i;
	int			len;
	char		*new_str;
	const char	*value;
	char		*name;
	char		*start;

	start = *str;
	i = -1;
	len = 0;
	new_str = ft_strchr(*str, '$');
	while (new_str[++i] && new_str[i] != ' ' && ((is_q == 1 &&
			new_str[i] != '\'') || (is_q == 2 && new_str[i] != '\"') || !is_q))
		len++;
	name = (char *)ft_calloc(len, sizeof(char));
	if (!name)
		return (-1);
	i = -1;
	while (new_str[++i + 1] && new_str[i + 1] != ' ' && ((is_q == 1 &&
			new_str[i + 1] != '\'') || (is_q == 2 && new_str[i + 1] != '\"') || !is_q))
		name[i] = new_str[i + 1];
	value = search_env_value(name, (const char **)env);
	free(name);
	name = new_str;
	new_str = ft_calloc(ft_strlen(*str) - len + ft_strlen(value) + 1, sizeof(char));
	i = 0;
	while (**str && *str != name)
	{
		new_str[i++] = **str;
		(*str)++;
	}
	while (*value)
		new_str[i++] = *value++;
	while (**str && **str != ' ' && ((is_q == 1 && **str != '\'') ||
			(is_q == 2 && **str != '\"') || !is_q))
		(*str)++;
	while (**str)
	{
		new_str[i++] = **str;
		(*str)++;
	}
	free(start);
	*str = new_str;
	return (0);
}

int	do_hast_quotes(char **str, char **env)
{
	int		is_q;
	char	*new_str;
	int		i;
	int		len;
	int		res;

	is_q = 0;
	i = -1;
	len = 0;
	res = 0;
	while ((*str)[++i] && !res)
	{
		if ((*str)[i] == '\'' && !is_q)
			is_q = 1;
		else if ((*str)[i] == '\"' && !is_q)
			is_q = 2;
		else if ((*str)[i] == '\"' && is_q == 2)
			is_q = 0;
		else if ((*str)[i] == '\'' && is_q == 1)
			is_q = 0;
		else if ((*str)[i] == '$' && is_q != 1)
		{
			res = replace_variables(str, env, is_q);
			i--;
		}
		else
			len++;
	}
	if (is_q)
		return (1);
	i = -1;
	new_str = (char *)calloc(len + 1, sizeof(char));
	if (!new_str)
		return (-1);
	res = 0;
	while ((*str)[++i] && res < len)
	{
		if ((*str)[i] == '\'' && !is_q)
			is_q = 1;
		else if ((*str)[i] == '\"' && !is_q)
			is_q = 2;
		else if ((*str)[i] == '\"' && is_q == 2)
			is_q = 0;
		else if ((*str)[i] == '\'' && is_q == 1)
			is_q = 0;
		else if ((*str)[i] == ' ' && is_q)
			new_str[res++] = 1;
		else
			new_str[res++] = (*str)[i];
	}
	free(*str);
	*str = new_str;
	return (0);
}

void	replace_spaces(char *str)
{
	while (*str)
	{
		if (*str == 1)
			*str = ' ';
		str++;
	}	
}