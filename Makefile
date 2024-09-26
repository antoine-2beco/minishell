# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:32:41 by ade-beco          #+#    #+#              #
#    Updated: 2024/09/26 12:25:14 by hle-roi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.c signal.c free_cmd.c data_utils.c
SRCBUILTINS := cd.c export.c export_print_utils.c echo.c env.c pwd.c unset.c exit.c
SRCPARSE := construct_tokens.c parser.c parse_utils.c expand.c expander_utils.c get_token.c handle_quotes.c handle_quotes_utils.c heredoc.c syntax.c syntax_utils.c
SRCSEXEC := executor.c run_builtins.c runcmd.c run_redir_utils.c ft_execve.c run_pipe_utils.c

OBJS := $(SRC:.c=.o)
OBJSBUILTINS := $(addprefix builtins/, $(SRCBUILTINS:.c=.o))
OBJSPARSE := $(addprefix parse/, $(SRCPARSE:.c=.o))
OBJSEXEC := $(addprefix execution/, $(SRCSEXEC:.c=.o))

CFLAGS := -Wall -Wextra -Werror -ggdb3 -I. 
#-fsanitize=address -g

CC := cc

NAME := minishell

READLINE := -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC)
	@$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(READLINE) -o $(NAME) $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC) libft/libft.a
	
	
clean :
	@$(MAKE) clean -C ./libft
	rm -f $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC)

fclean : clean
	@$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus