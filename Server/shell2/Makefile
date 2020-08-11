



minishell = minishell

src = main.c env.c minishell.c unsetenv.c setenv.c exit.c echo.c utils.c system.c cd.c

obj	= $(src:.c=.o)

src_dir = src/

obj_dir = obj/

srcs = $(addprefix $(src_dir), $(src))
objs = $(addprefix $(obj_dir), $(obj))

flags = -Wall -Wextra

all:
	make -C alylibc
	gcc -c $(flags)  $(srcs)
	ar rc shell.a $(obj)
	mv $(obj) $(obj_dir)

clean:
	make clean -C alylibc
	rm -f $(objs)
	
fclean:
	make fclean -C alylibc
	rm -f $(objs)
	rm -f shell.a

re: fclean all


