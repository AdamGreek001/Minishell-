# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 11:43:22 by akharfat          #+#    #+#              #
#    Updated: 2024/12/25 19:09:02 by eel-alao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	builtins/builtins.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c \
			builtins/export.c builtins/pwd.c env/env.c env/env_utils1.c env/env_utils2.c \
			execution/exec.c execution/exit_status.c execution/handle_reder.c execution/list.c \
			execution/list_utils.c execution/signals.c execution/utils.c minishell.c parce/expand.c \
			parce/heredoc.c parce/parce.c parce/parce2.c parce/parce3.c parce/parce4.c utils/ft_split.c utils/pool_split.c utils/utils.c \
			utils/utils2.c utils/utils3.c utils/utils4.c garbage_collector/g_collector.c \
			builtins/builtins_utils.c execution/exec_utils.c
NAME	=	minishell
CC		=	cc
HEADER	=	minishell.h struct.h
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address
OBJS	=	$(SRC:.c=.o)

READLINE_L = ~/.brew/opt/readline/lib
READLINE_I = ~/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -L $(READLINE_L) -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -I $(READLINE_I) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
