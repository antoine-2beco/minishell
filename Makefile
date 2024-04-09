SRC := main.c parse/construct_tokens.c parse/parser.c parse/parse_utils.c parse/expander.c parse/expander_utils.c parse/get_token.c

OBJS := $(SRC:.c=.o)

CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g

CC := cc

NAME := minishell

READLINE := -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./ft_printf
	$(CC) $(CFLAGS) $(READLINE) -I ./minilib.h $(OBJS) libft/libft.a ft_printf/libftprintf.a -o $(NAME)
	
	
clean :
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./ft_printf
	rm -f $(OBJS)

fclean : clean
	@$(MAKE) fclean -C ./libft
	@$(MAKE) fclean -C ./ft_printf
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus