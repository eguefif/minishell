NAME = minishell
CC = gcc
CFLAG = -g -Wall -Werror -Wextra
LIB = -lft -L./libft
LIBFT = ./libft/libft.a
INC = -Iincludes -I./libft/includes

_SRC = main.c
_OBJ = $(_SRC:.c=.o)
ODIR = ./src/
SDIR = ./src/
OBJ = $(addprefix $(ODIR), $(_OBJ))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIB) -o $@

$(LIBFT):
	make -C ./libft

$(ODIR)%.o: $(SDIR)%.c ./includes/minishell.h
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf ./libft/libft.a

re: fclean all
	make -C ./libft re
