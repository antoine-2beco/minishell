SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_memcmp.c \

BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		#ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

BONUS_OBJS = $(BONUS:.c=.o)

OBJS = $(SRC:.c=.o)

INCLUDES = -I libft.h

CFLAGS = -Wall -Wextra -Werror

CC = gcc

NAME = libft.a

all : $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "\033[92mLibft successfuly compiled\033[0m"

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJS) :
	@$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.c) -o $@

$(BONUS_OBJS) :
	@$(CC) $(CFLAGS) $(INCLUDES) -c $(@:.o=.c) -o $@
	
clean :
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus