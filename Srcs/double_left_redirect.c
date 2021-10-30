/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 03:33:52 by vlucilla          #+#    #+#             */
/*   Updated: 2021/10/30 04:02:08 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_n(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("\0");
	if (!s2)
		s2 = ft_strdup("\0");
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = '\n';
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	free(s1);
	return (str);
}

void	do_double_left_child(char *file, int fd)
{
	int		len;
	char	*tmpline;
	char	*line;

	line = NULL;
	tmpline = NULL;
	len = ft_strlen(file);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, file, len + 1))
			break ;
		tmpline = ft_join_n(tmpline, line);
	}
	line = ft_strtrim(tmpline, "\n");
	free(tmpline);
	ft_putendl_fd(line, fd);
	free(line);
	close(fd);
}

int	do_double_left_redirect(char *file, char *str, char ***env)
{
	int	res;
	int	fd[2];

	pipe(fd);
	res = 0;
	if (fork() == 0)
	{
		close(fd[0]);
		do_double_left_child(file, fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(NULL);
		res = do_command(str, env);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	return (res);
}
