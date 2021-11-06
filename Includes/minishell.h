/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:25:01 by wgaunt            #+#    #+#             */
/*   Updated: 2021/11/06 00:38:59 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

# define R_RDR 2
# define L_RDR 3
# define DR_RDR 4
# define DL_RDR 5
# define ERROR_MALLOC_MSG "minishell: Not enough free memory"
# define ERR_CODE -1
# define ERROR_EMPTYPIPE_MSG "minishell: Syntax error near \"|\""
# define ERROR_QUOTES_MSG "minishell: Not closed quotes founded"

extern int	g_sh_exit;

typedef struct s_line_element
{
	char	*text;
	int		iscommand;
}				t_line_element;
typedef struct s_command
{
	char	*text;
	int		fd[2];
}				t_command;

int		do_exit(char **arr, t_list *words, t_list *com, char ***env);
int		do_echo(t_list *line_element);					
int		do_cd(t_list *line_element, char ***env);
int		do_pwd(void);
int		do_export(t_list *line_element, char ***env);
int		do_unset(t_list *line_element, char ***env);
int		do_env(char **env, char **arr);
int		exit_shell(void);
int		error_errno(void);
t_list	*pipe_split(char *line);
void	t_command_clear(void *elem);
int		q_error(int res);
char	*ft_strchrq(const char *s, int ch);
int		is_correct_var(char *str, int can_eq);
int		env_cpy(char ***my_env, char **env);
int		add_env(const char *new_env_var, char ***env);
int		remove_var(const char *var, char ***env);
int		change_env_var(const char *var, char ***env);
char	*search_env_value(const char *name, const char **env);
char	**search_env(const char *name, char **env);
int		name_strncmp(const char *name, const char *var, int len);
char	**space_split(char const *s);
int		parse_com(char *line, char ***env);
char	*substr_word(char *str, const char *delims);
void	free_array(char **arr);
int		parse_redir(t_list *com, char ***env);
int		do_redirects(int type, char *file, t_list *com, char ***env);
int		do_command(int is_p, t_list *command, char ***env);
int		do_builtins(char **arr, char ***env, t_list *com);
int		is_builtin(char *line);
int		do_pipes(t_list *com, t_command *next, char ***env);
int		do_hast_quotes(char **str, char **env);
int		cut_file(char **str, char **file, int type, char **env);
int		find_type(char *str);
void	free_list(t_list *lst);
char	*change_name_to_value(char **str, char *new_str, char *value, int i);
char	*take_value(char *str, char **env, int *len);
int		find_path(char **path, char **env);
void	do_double_left_child(char *file, int fd0, int fd);
int		do_double_left_redirect(char *file, t_list *com, char ***env);
void	execve_err(char *str);
int		pars_err(char *trim_com, t_command *new_com);
#endif
