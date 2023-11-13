NAME = minishell
CC = gcc
CFLAG = -g -Wall -Werror -Wextra
INC = -Iincludes -I$(LIBFT_DIR)/includes -I$(READLINE_DIR)

LIB = -lft -L$(LIBFT_DIR) -L$(READLINE_DIR) -lreadline
LIB_DIR = ./lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = $(LIB_DIR)/readline-8.2
READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_SRC = $(LIB_DIR)/readline-8.2.tar.gz
READLINE = $(READLINE_DIR)/libreadline.a

_SRC = main.c
_OBJ = $(_SRC:.c=.o)
ODIR = ./src/
SDIR = ./src/
OBJ = $(addprefix $(ODIR), $(_OBJ))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(READLINE)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(READLINE):
	@if [ ! -d $(READLINE_DIR) ] ; then \
		curl $(READLINE_URL) -o $(READLINE_SRC) ; \
		tar -xvf $(READLINE_SRC) -C $(LIB_DIR); \
		rm $(READLINE_SRC) ; \
	fi
	@cd $(READLINE_DIR) ; \
	./configure ; \
	make 

$(ODIR)%.o: $(SDIR)%.c ./includes/minishell.h
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

build_test_env:
	python3 -m venv ./test/venv
	@echo "Type: source ./test/venv/bin/activate && make build_dependences"

build_dependences:
	pip install -r ./test/requirements.txt

test_acceptances:
	pytest

.PHONY: all clean fclean re build_test_env build_dependences

clean:
	rm -rf $(OBJ)
	@if [ -d $(READLINE_DIR) ] ; then \
		make -C $(READLINE_DIR) clean ; \
	fi

fclean: clean
	rm -rf $(NAME)
	rm -rf ./libft/libft.a
	rm -rf $(READLINE_DIR)

re: fclean all
	make -C ./libft re
