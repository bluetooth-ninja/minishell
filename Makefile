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
	$(CC) $(FLAGS) -I$(INCLUDE) $(SRC) -lreadline -I$(LIBFTPATH) $(LIBFT) -o $(NAME) 

.PHONY: all
all: $(NAME)

$(LIBFT):
	make bonus -C $(LIBFTPATH)

.PHONY: clean
clean:
	make fclean -C $(LIBFTPATH)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: bonus
bonus: