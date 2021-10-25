/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:56:23 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/26 00:36:45 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

char	*ft_strchrq(const char *s, int ch)
{
	char	*s1;
	int		is_q;

	is_q = 0;
	s1 = (char *)s;
	while (*s1)
	{
		if (*s1 == '\'' && !is_q)
			is_q = 1;
		else if (*s1 == '\"' && !is_q)
			is_q = 2;
		else if (*s1 == '\'' || *s1 == '\"')
			is_q = 0;
		else if (*s1 == ch && !is_q)
			return (s1);
		s1++;
	}
	if (*s1 == '\0' && ch == '\0')
		return (s1);
	return (NULL);
}

int	env_cpy(char ***my_env, char **env)
{
	int	i;

	i = 0;
	if (!my_env)
		return (1);
	while (env[i] != 0)
		i++;
	*my_env = malloc(sizeof(char *) * (i + 1));
	(*my_env)[i] = 0;
	i--;
	while (i >= 0)
	{
		(*my_env)[i] = ft_strdup(env[i]);
		i--;
	}
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

/*
char	*substr_word(char *str, const char *delims)
{
	char	*word;
	int		i;

	word = NULL;
	if (!str)
		return (0);
	i = 0;
	while (!ft_strchr(delims, str[i]))
		i++;
	if (i > 0)
	{
		word = (char *)malloc(sizeof(char) * i);
		if (!word)
			return (0);
		ft_strlcpy(word, str, i);
	}
	return (word);
}
*/