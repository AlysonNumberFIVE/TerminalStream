

network = stable_network/
network_lib = network.a

netlib = $(addprefix $(network), $(network_lib))


shell = shell/
shell_lib = shell.a

shelllib = $(addprefix $(shell), $(shell_lib))

alylibc_a = alylibc/lib.a
ft = libft.a

alylib = $(addprefix $(shell), $(alylibc_a))
libft = $(addprefix $(shell), $(ft))

server:
	make lib -C $(network)
	make -C $(shell)
	gcc -o server supervisor.c $(shelllib) $(netlib) $(alylib) $(libft)

clean:
	make clean -C $(network)
	make clean -C $(shell)
	
fclean:
	make fclean -C $(network)
	make fclean -C $(shell)
	rm -f server

re: fclean server
