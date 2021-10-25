# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlucilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 16:22:11 by wgaunt            #+#    #+#              #
#    Updated: 2021/10/26 01:19:05 by vlucilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRC =	Srcs/parser.c Srcs/redirect_parsing.c Srcs/redirects.c Srcs/pipes.c Srcs/do_builtin.c \
		Srcs/replace_symbols.c Srcs/cut_file.c Srcs/space_split.c Srcs/utils.c Srcs/Builtins/utils.c \
		Srcs/minishell.c Srcs/Builtins/utils2.c Srcs/Builtins/cd.c Srcs/Builtins/echo.c Srcs/Builtins/env.c \
		Srcs/Builtins/exit.c Srcs/Builtins/export.c Srcs/Builtins/pwd.c Srcs/Builtins/unset.c

LIBFT 		= Libft/libft.a
LIBFTPATH	= Libft/

INCLUDE	= Includes/
FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
RLFLAGS	= -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -lreadline 
CC		= gcc

$(NAME): $(SRC) $(LIBFT)
	@$(CC) $(FLAGS) -I$(INCLUDE) $(SRC) -lreadline -I$(LIBFTPATH) $(LIBFT) -o $(NAME)
	@printf "\e[37;5;44m              MINISHELL IS READY                \e[0m\n"
	@printf "\e[30;5;42m                    Enjoy🤗                     \e[0m\n"

.PHONY: all
all: $(NAME)

$(LIBFT):
	@make -C $(LIBFTPATH)
	@printf "\e[37;5;45m               Libft is ready✅                  \e[0m\n"

.PHONY: clean
clean:
	@make fclean -C $(LIBFTPATH)
	@printf "\e[30;5;47m                Clean done.🧹                   \e[0m\n"

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@printf "\e[30;5;42m                Fclean done.🧹                  \e[0m\n"

.PHONY: re
re: fclean all

.PHONY: bonus
bonus: