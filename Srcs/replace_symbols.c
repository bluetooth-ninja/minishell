/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:33:15 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/29 00:55:11 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_variables(char **str, char **env, int is_q)
{
	int		len;
	char	*new_str;
	char	*value;
	char	*start;

	start = *str;
	len = 0;
	value = take_value(*str, env, is_q, &len);
	if (!value)
		return (ERROR_MALLOC_CODE);
	new_str = ft_calloc(ft_strlen(*str) - len + ft_strlen(value) + 1,
			sizeof(char));
	if (!new_str)
	{
		free(value);
		return (ERROR_MALLOC_CODE);
	}
	*str = change_name_to_value(str, new_str, value, is_q);
	free(start);
	free(value);
	return (0);
}

int	find_is_q(char ch, int is_q)
{
	if (ch == '\'' && !is_q)
		is_q = 1;
	else if (ch == '\"' && !is_q)
		is_q = 2;
	else if (ch == '\"' && is_q == 2)
		is_q = 0;
	else if (ch == '\'' && is_q == 1)
		is_q = 0;
	return (is_q);
}

int	quotes_len_plus_var(char **str, char **env)
{
	int	i;
	int	is_q;
	int	res;
	int	len;

	len = 0;
	i = -1;
	is_q = 0;
	res = 0;
	while (*str && (*str)[++i] && !res)
	{
		is_q = find_is_q((*str)[i], is_q);
		if ((*str)[i] == '$' && is_q != 1)
		{
			res = replace_variables(str, env, is_q);
			i--;
		}
		else if ((*str)[i] != '\'' && (*str)[i] != '\"')
			len++;
	}
	if (res || !(*str))
		return (-1);
	if (is_q)
		return (-2);
	return (len);
}

void	new_str_create(char **str, char *new_str, int len)
{
	int	i;
	int	new_i;
	int	is_q;

	i = -1;
	new_i = 0;
	is_q = 0;
	while ((*str)[++i] && new_i < len)
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
			new_str[new_i++] = 1;
		else
			new_str[new_i++] = (*str)[i];
	}
}

int	do_hast_quotes(char **str, char **env)
{
	char	*new_str;
	int		len;

	len = quotes_len_plus_var(str, env);
	if (len == -2 || len == -1)
		return (len);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (ERROR_MALLOC_CODE);
	new_str_create(str, new_str, len);
	free(*str);
	*str = new_str;
	return (0);
}
