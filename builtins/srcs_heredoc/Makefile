NAME = heredoc
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
INC = -I. -I$(LIBFT_DIR)/includes

LIB = -lft -L$(LIBFT_DIR)
LIB_DIR = ../../lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

_SRC = $(NAME).c
OBJ = $(_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@
	cp $(NAME) ../$(NAME)

%.o: %.c ./$(NAME).h
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf ../$(NAME)

re : fclean all
