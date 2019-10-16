all: sendmassage receivemessage range comm packser packclient
sendmassage: sendmsg.c
	gcc sendmsg.c -o send -pthread
receivemessage: server.c
	gcc server.c -o rev -pthread
range:	myrange.c
	gcc myrange.c -o range
comm:	command1.c
	gcc command1.c -o com1
packser: fclient.c
	gcc fclient.c -o client
packclient: fserver.c
	gcc fserver.c -o server

