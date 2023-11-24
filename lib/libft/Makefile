NAME = libft.a
CC = gcc -Wall -Werror -Wextra -g
LIB = -lft -L./lib
IFILE = -I./includes
AR = /usr/bin/ar rcs

_SRC = \
	ft_printf.c clean.c splitter.c init_splits.c displayer.c replacer.c \
	init_conversionspe.c init_conversionspe_utils.c make_int.c \
	make_replacement_utils.c make_str.c make_percentage.c make_char.c \
	make_ptr.c make_uint.c make_precision.c make_double.c\
	ft_putchar.c ft_putstr.c ft_strcat.c ft_strcmp.c ft_strlcat.c ft_strcat.c \
	ft_strncat.c ft_strncmp.c ft_strstr.c ft_putnbr.c ft_putnbr_fd.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putendl.c ft_itoa.c ft_memalloc.c \
	ft_memdel.c ft_strnew.c ft_strcpy.c ft_strncpy.c ft_strlen.c ft_strdel.c ft_cleansplits.c\
	ft_strclr.c ft_strtrim.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strchr.c ft_strrchr.c ft_strnstr.c ft_toupper.c ft_tolower.c ft_striter.c ft_striteri.c \
	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strdup.c ft_atoi.c ft_strjoin.c\
	ft_isspace.c ft_substr.c ft_split.c ft_strlcpy.c ft_calloc.c ft_lutoa_base.c \
	get_next_line.c get_next_line_utils.c ft_atoi_base.c ft_strldup.c ft_strjoin_tab.c ft_is_strnum.c
_OBJ = $(_SRC:.c=.o)
ODIR = ./src/
SDIR = ./src/
OBJ = $(addprefix $(ODIR), $(_OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

libft.so: $(OBJ)
	$(CC) -shared -o $@ $^	

$(ODIR)%.o: $(SDIR)%.c includes/libft.h
	$(CC) -c $< $(IFILE) -o $@

.PHONY: clean fclean re

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
