

NAME = lib

SRC_NAME = strtrim.c \
	   arraylen.c \
	   arraypush.c \
           charpush.c \
           count_args.c \
           free2d.c \
           free_and_null.c \
           itoa.c join.c \
           my_isspace.c \
           read_buffer.c \
           split.c sub.c \
           normalize_string.c \
           ft_memset.c \
           ft_bzero.c \
           ft_strcat.c \
           ft_strcpy.c \
           ft_strcmp.c \
           ft_strlen.c \
           ft_strdup.c \
           ft_strstr.c \
           ft_strchr.c \
           map_file.c \
	   flag_support.c \
	   error_and_exit.c \
	   fmap_file.c

OBJ = $(SRC_NAME:.c=.o)


SRC = src/*.c

LIB = lib.a

$(NAME):
	gcc -Wall -Wextra -c $(SRC)
	ar rc $(LIB) $(OBJ)
	mv $(OBJ) obj

all: $(NAME)

clean:
	rm -rf obj/*.o

fclean:
	rm -rf obj/*.o
	rm -rf $(LIB)

re: fclean all
