CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./libft -lft -lreadline

NAME = minishell
LIBFT = libft/libft.a

SRCS =	minishell.c \
		parsing/parsing.c \
		built_in/ft_echo.c \
		built_in/ft_pwd.c
		built_in/cd.c
		
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I./libft -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
