



test_file_send_dir = side1/

test_file_recv_dir = side2/

src = file_send_recv.c init_client.c c_version.c init_server.c

obj = $(src:.c=.o)

test_file_send_src = helloFileSender.c

test_file_recv_src = helloFileRecv.c

sendbin = sender
recvbin = recv


sender = $(addprefix $(test_file_send_dir), $(test_file_send_src))
receiver = $(addprefix $(test_file_recv_dir), $(test_file_recv_src))

send = $(addprefix $(test_file_send_dir), $(sendbin))
recv = $(addprefix $(test_file_recv_dir), $(recvbin))

all:
	gcc -o $(send) $(sender) $(src)
	gcc -o $(recv) $(receiver) $(src)

lib:
	gcc -c $(src)
	ar rc network.a $(obj)

clean:
	rm -f $(obj)

fclean:
	rm -f $(obj)
	rm -f network.a

