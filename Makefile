# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 16:22:11 by wgaunt            #+#    #+#              #
#    Updated: 2021/11/06 18:18:13 by vlucilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC			=	Srcs/parser.c Srcs/redirect_parsing.c Srcs/redirects.c Srcs/pipes.c Srcs/do_builtin.c Srcs/clear.c Srcs/find_path.c \
				Srcs/replace_symbols.c Srcs/replace_symbols2.c Srcs/cut_file.c Srcs/space_split.c Srcs/utils.c Srcs/Builtins/utils.c \
				Srcs/minishell.c Srcs/double_left_redirect.c Srcs/Builtins/utils2.c Srcs/Builtins/cd.c Srcs/Builtins/echo.c Srcs/Builtins/env.c \
				Srcs/Builtins/exit.c Srcs/Builtins/export.c Srcs/Builtins/pwd.c Srcs/Builtins/unset.c Srcs/command_exec.c

OBJS 		= 	$(SRC:.c=.o)
DEPS 		=	$(SRC:.c=.d)

LIBFTPATH	= Libft/

#RLFLAGS	= -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -lreadline 
CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror# -fsanitize=address -g3
CPPFLAGS 	= 	-MMD -I./Libft -I./Includes 
RM			=	rm -f
LIB			= 	-lreadline Libft/libft.a

all: 		$(NAME)

$(NAME): 	$(OBJS) Makefile
			@$(MAKE) -C $(LIBFTPATH)
			@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
			@printf "\e[37;5;44m              MINISHELL IS READY                \e[0m\n"
			@printf "\e[30;5;42m                    Enjoy🤗                     \e[0m\n"

.c.o:
			@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

-include $(DEPS)

clean:
	@make fclean -C $(LIBFTPATH)
	@rm -f $(OBJS) $(DEPS)
	@printf "\e[30;5;47m                 Clean done.🧹                  \e[0m\n"

fclean: clean
	@rm -f $(NAME)
	@printf "\e[30;5;42m                 Fclean done.🧹                 \e[0m\n"

re: fclean all

.PHONY: all clean fclean re