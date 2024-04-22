SRC := main.c
SRCBUILTINS := builtins/cd.c builtins/export.c
SRCPARSE := parse/construct_tokens.c parse/parser.c parse/parse_utils.c parse/expander.c parse/expander_utils.c parse/get_token.c
SRCSEXEC := execution/executor.c execution/pipex.c execution/free_cmd.c

OBJS := $(SRC:.c=.o)
OBJSBUILTINS := $(SRCBUILTINS:.c=.o)
OBJSPARSE := $(SRCPARSE:.c=.o)
OBJSEXEC := $(SRCSEXEC:.c=.o)

CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g

CC := cc

NAME := minishell

READLINE := -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./ft_printf
	$(CC) $(CFLAGS) $(READLINE) -I ./minilib.h $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC) libft/libft.a ft_printf/libftprintf.a -o $(NAME)
	
	
clean :
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./ft_printf
	rm -f $(OBJS) $(OBJSBUILTINS) $(OBJSPARSE) $(OBJSEXEC)

fclean : clean
	@$(MAKE) fclean -C ./libft
	@$(MAKE) fclean -C ./ft_printf
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus