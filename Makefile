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

build_test_env:
	mkdir test
	python3 -m venv ./test/venv
	@echo "Type: source ./test/venv/bin/activate"

build_dependences:
	python3 -m pip install -- upgrade pip
	python3 -r ./test/requirements.txt

.PHONY: all clean fclean re build_test_env build_dependences

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf ./libft/libft.a

re: fclean all
	make -C ./libft re
