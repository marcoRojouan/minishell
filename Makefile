CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./libft -lft -lreadline

NAME = minishell
LIBFT = libft/libft.a
OBJ_DIR = obj

SRCS =	minishell.c \
		free_cmd.c \
		signal.c \
		parsing/parsing.c \
		parsing/parsing_utils.c \
		parsing/ft_split_args.c \
		parsing/ft_split_args_utils.c \
		parsing/sort_line.c \
		parsing/expand.c \
		parsing/expand_utils.c \
		parsing/copy_env.c \
		parsing/remove_quotes.c \
		built_in/ft_echo.c \
		built_in/ft_pwd.c \
		built_in/cd_env_utils.c \
		built_in/ft_cd.c \
		built_in/ft_exit.c \
		built_in/ft_export.c \
		built_in/ft_env.c \
		built_in/ft_unset.c \
		built_in/export_utils.c \
		built_in/export_utils_bis.c \
		exec/exec_pipeline.c \
		exec/fd_gestion.c \
		exec/execution.c \
		exec/path_finder.c \
		exec/exec_builtins.c \
		exec/exec_one_cmd.c \
		exec/heredoc.c \
		exec/exec_cmd.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./libft -I. -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
