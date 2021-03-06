/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:33:15 by vlucilla          #+#    #+#             */
/*   Updated: 2021/11/08 03:23:06 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_variables(char **str, char **env, int i, int is_q)
{
	int		len;
	char	*new_str;
	char	*value;
	char	*start;

	start = *str;
	len = 0;
	value = take_value(&((*str)[i]), env, &len);
	if (!value)
		return (ERR_CODE);
	new_str = ft_calloc(ft_strlen(*str) - len + ft_strlen(value) + 1, 1);
	if (!new_str)
	{
		free(value);
		return (ERR_CODE);
	}
	*str = change_name_to_value(str, new_str, value, i);
	free(start);
	if ((ft_strchr(value, ' ') || !(*value)) && !is_q)
	{
		free(value);
		return (1);
	}
	free(value);
	return (0);
}

int	function_action(char **str, int *is_q, char **env, int *len)
{
	int	res;
	int	i;

	i = -1;
	res = 0;
	while (*str && (*str)[++i] && res != ERR_CODE)
	{
		if ((*str)[i] == '\'' && !(*is_q))
			*is_q = 1;
		else if ((*str)[i] == '\"' && !(*is_q))
			*is_q = 2;
		else if ((*str)[i] == '\"' && *is_q == 2)
			*is_q = 0;
		else if ((*str)[i] == '\'' && *is_q == 1)
			*is_q = 0;
		else if ((*str)[i] == '$' && (ft_isalnum((*str)[i + 1])
				|| (*str)[i + 1] == '_' || (*str)[i + 1] == '?') && *is_q != 1)
			res = replace_variables(str, env, i--, *is_q);
		else
			(*len)++;
	}
	return (res);
}

static int	quotes_len_plus_var(char **str, char **env, int is_file)
{
	int	is_q;
	int	res;
	int	len;

	len = 0;
	is_q = 0;
	res = function_action(str, &is_q, env, &len);
	if (res == 1 && is_file)
		return (-3);
	if (res == ERR_CODE || !(*str))
		return (ERR_CODE);
	if (is_q)
		return (-2);
	return (len);
}

static void	new_str_create(char **str, char *new_str, int len)
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

int	do_hast_quotes(char **str, char **env, int is_file)
{
	char	*new_str;
	int		len;

	len = quotes_len_plus_var(str, env, is_file);
	if (len == -2)
	{
		g_sh_exit = 2;
		ft_putendl_fd(ERROR_QUOTES_MSG, 2);
		return (len);
	}
	if (len == ERR_CODE)
		return (ERR_CODE);
	if (len == -3)
		return (-3);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (ERR_CODE);
	new_str_create(str, new_str, len);
	free(*str);
	*str = new_str;
	return (0);
}
