CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I.
CLIB = -c

SRC_FILES = src/main.c utils/error_handling.c \
			utils/processes_utils.c utils/ft_free.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = pipex

LIBFT = ./libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CLIB) $^ -o $@

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: clean fclean all

.PHONY: clean fclean all