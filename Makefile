# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:32:41 by ade-beco          #+#    #+#              #
#    Updated: 2024/06/21 15:59:32 by hle-roi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC := main.c
SRCBUILTINS := cd.c export.c echo.c env.c pwd.c unset.c exit.c
SRCPARSE := construct_tokens.c parser.c parse_utils.c expander.c expander_utils.c get_token.c
SRCSEXEC := executor.c free_cmd.c run_builtins.c

OBJS := $(SRC:.c=.o)
OBJSBUILTINS := $(addprefix builtins/, $(SRCBUILTINS:.c=.o))
OBJSPARSE := $(addprefix parse/, $(SRCPARSE:.c=.o))
OBJSEXEC := $(addprefix execution/, $(SRCSEXEC:.c=.o))

CFLAGS := -Wall -Wextra -Werror 
#-fsanitize=address -g

CC := cc

NAME := minishell

READLINE := -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC)
	@$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(READLINE) -I ./minilib.h $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC) libft/libft.a -o $(NAME)
	
	
clean :
	@$(MAKE) clean -C ./libft
	rm -f $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC)

fclean : clean
	@$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus