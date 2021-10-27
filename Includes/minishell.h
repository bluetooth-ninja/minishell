/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:25:01 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/26 13:35:19 by wgaunt           ###   ########.fr       */
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

extern int sh_exit;

typedef struct	s_line_element
{
	char	*text;
	int		iscommand;
}				t_line_element;

typedef struct	s_command
{
	char	*text;
	int		fd[2];
}				t_command;

/* Структура, которая будет использоваться в списках                            */
/* Как выглядит список (t_list из libft):                                       */
/* {                                                                            */
/*     void    *content;    тут будет храниться указатель на t_line_element     */
/*     t_list  *next;                                                           */
/* }                                                                            */

/* Прототипы конечных функций. Скорее всего потом в отдельный файл переместятся */

/* Возвращаемое значение показывает наличие ошибки и мб код ошибки              */
/* Пока просто необходимо учитывать его наличичие и сохранять в переменную      */
/* Предполагается что line_element при вызове указывает на элемент с командой   */


/* Любые do_ функции не обрабатывают ошибку в случае неправильного числа аргументов на вход */
/*    и принимают t_list со стартовым элементом - командой (не проверяют на корректность)   */
/*   Также необходимо обработать преобразование имени переменных в текст до вызова функций  */

int			do_exit(char **arr);
int			do_echo(t_list *line_element);					// Не работает тест для аргументов со спец. символами
int			do_cd(t_list *line_element, char ***env);
int			do_pwd();
int			do_export(t_list *line_element, char ***env);
int			do_unset(t_list *line_element, char ***env);	// Нет проверки на 0 аргументов
int			do_env(char **env);
int			exit_shell();									// Будет использоваться при всяком завершении работы. Нужно передавать все для очистки если будем чистить

char		*ft_strchrq(const char *s, int ch);
int			env_cpy(char ***my_env, char **env);
int			add_env(const char *new_env_var, char ***env);
int			remove_var(const char *var, char ***env);
int			change_env_var(const char *var, char ***env);
const char	*search_env_value(const char *name, const char **env);
char		**search_env(const char *name, char **env);
int			name_strncmp(const char *name, const char *var, int len);
char		**space_split(char const *s);
int			parse_com(char *line, char ***env);
char		*substr_word(char *str, const char *delims);
void		free_array(char **arr);
int			parse_redir(char *str, char ***env);
int 		do_redirects(int type, char *file, char *str, char ***env);
int			do_command(char *str, char ***env);
int			do_builtins(char **arr, char ***env);
int			is_builtin(char *line);
int			do_pipes(t_command *cur, t_command *next, char ***env);
int			do_hast_quotes(char **str, char **env);
int			cut_file(char **str, char **file, int type);
void		free_list(t_list *lst);

#endif