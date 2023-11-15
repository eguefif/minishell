NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
INC = -Iincludes -I$(LIBFT_DIR)/includes -I$(READLINE_DIR)

LIB = -lft -L$(LIBFT_DIR) -lncurses -L$(READLINE_DIR) -lreadline
LIB_DIR = ./lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = $(LIB_DIR)/readline-8.2
READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_SRC = $(LIB_DIR)/readline-8.2.tar.gz
READLINE = $(READLINE_DIR)/libreadline.a

_SRC_LIB_STATIC = parser.c executer.c cleaner.c lexer.c lexer_get_tokens.c error.c
#_SRC = main.c parser.c executer.c cleaner.c lexer.c lexer_get_tokens.c error.c
_SRC = main.c $(_SRC_LIB_STATIC)
_OBJ = $(_SRC:.c=.o)
_OBJ_LIB_STATIC = $(_SRC_LIB_STATIC:.c=.o)
ODIR = ./src/obj/
SDIR = ./src/
OBJ = $(addprefix $(ODIR), $(_OBJ))
OBJ_LIB_STATIC = $(addprefix $(ODIR), $(_OBJ_LIB_STATIC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(READLINE)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@
	cp ./minishell ./test/

$(LIBFT):
	make -C $(LIBFT_DIR)

$(READLINE):
	@if [ ! -d "$(READLINE_DIR)" ] ; then \
		curl $(READLINE_URL) -o $(READLINE_SRC) ; \
		tar -xvf $(READLINE_SRC) -C $(LIB_DIR); \
		rm $(READLINE_SRC) ; \
	fi
	@cd $(READLINE_DIR) ; \
	./configure ; \
	make 

$(ODIR)%.o: $(SDIR)%.c ./includes/minishell.h
	@if [ ! -d "$(ODIR)" ] ; then \
		mkdir -p $(ODIR); \
	fi
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

build_test_env:
	python3 -m venv ./test/venv
	@echo "Type: source ./test/venv/bin/activate && make build_dependencies"

build_dependencies:
	pip install -r ./test/requirements.txt

unit_test: libminishell.a
	@cd test; \
	pytest test_unit.py -vv

libminishell.a: $(OBJ_LIB_STATIC)
	ar -rcs $@ $^
	mv libminishell.a test/unit_tests/libminishell.a

test:
	@cd test; \
	pytest test_acceptances.py -vv

.PHONY: all clean fclean re build_test_env build_dependencies test 

clean:
	rm -rf $(OBJ)
#	@if [ -d $(READLINE_DIR) ] ; then \
#		make -C $(READLINE_DIR) clean ; \
#	fi

fclean: clean
	rm -rf $(NAME)
	@if [ -d "$(ODIR)" ] ; then \
		rm -r $(ODIR) ; \
	fi
	rm -rf ./libft/libft.a
#	rm -rf $(READLINE_DIR)

re: fclean all
	make -C $(LIBFT_DIR) re
