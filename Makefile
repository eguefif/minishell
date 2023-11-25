NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra #-fsanitize=address
INC = -Iincludes -I$(LIBFT_DIR)/includes -I$(READLINE_DIR)

LIB = -lft -L$(LIBFT_DIR) -lncurses -L$(READLINE_DIR) -lreadline
LIB_DIR = ./lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = $(LIB_DIR)/readline-8.2
READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_SRC = $(LIB_DIR)/readline-8.2.tar.gz
READLINE = $(READLINE_DIR)/libreadline.a

_SRC_LIB_STATIC = parser.c executer.c cleaner.c lexer.c lexer_get_tokens.c error.c \
				  parser_get_commands.c parser_clean_commands1.c init.c exit.c \
				  parser_clean_commands2.c lexer_count_tokens.c \
				  lexer_get_token_size.c parser_get_commands_populate.c utils.c executer_getpath.c \
				  environment.c signals.c builtin.c heredoc.c parser_clean_commands_stdin.c heredoc_utils.c \
				  builtin_export.c builtin_echo_env.c signal2.c environment_remove_var.c

_SRC = main.c $(_SRC_LIB_STATIC)
_OBJ = $(_SRC:.c=.o)
_OBJ_LIB_STATIC = $(_SRC_LIB_STATIC:.c=.o)
ODIR = ./src/obj/
SDIR = ./src/
OBJ = $(addprefix $(ODIR), $(_OBJ))
OBJ_LIB_STATIC = $(addprefix $(ODIR), $(_OBJ_LIB_STATIC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(READLINE) #$(BUILTINS)
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

test: test_memory unit_test test_segfault
	@cp ./minishell ./test
	@cd test; \
	pytest test_acceptances.py -vv

test_memory:
	@cp ./minishell ./test
	@cd test; \
	pytest test_memory.py -vv

test_segfault:
	@cp ./minishell ./test/segfault_test
	cd test/segfault_test; \
		pytest segfault.py

val:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s --show-leak-kinds=all --suppressions=./test/supp.txt ./minishell

.PHONY: all clean fclean re build_test_env build_dependencies test val test_memory

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_DIR) clean
	@for builtin in $(_BUILTINS); do \
		echo make -C $(BUILTIN_DIR)/srcs_$${builtin} clean; \
		make --silent -C $(BUILTIN_DIR)/srcs_$${builtin} clean; \
	done
#	@if [ -d $(READLINE_DIR) ] ; then \
#		make -C $(READLINE_DIR) clean ; \
#	fi

fclean: clean
	rm -rf $(NAME)
	@if [ -d "$(ODIR)" ] ; then \
		rm -r $(ODIR) ; \
	fi
	rm -rf $(LIBFT_DIR)/libft.a
	@for builtin in $(_BUILTINS); do \
		echo make -C $(BUILTIN_DIR)/srcs_$${builtin} fclean; \
		make --silent -C $(BUILTIN_DIR)/srcs_$${builtin} fclean; \
	done
#	rm -rf $(READLINE_DIR)

re: fclean all
