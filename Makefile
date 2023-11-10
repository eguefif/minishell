NAME = minishell
CC = gcc
CFLAG = -g -Wall -Werror -Wextra
LIB = -lft -L./libft
INC = -Iincludes -I./libft/includes

_SRC = main.c
_OBJ = $(_SRC:.c=.o)
ODIR = ./src/
SDIR = ./src/
OBJ = $(addprefix $(ODIR), $(_OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIB) -o $@

$(ODIR)%.o: $(SDIR)%.c ./includes/minishell.h
	$(CC) $(CFLAGS) -c $< $(INC) -o $@
