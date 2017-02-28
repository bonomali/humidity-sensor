server.o: server.c post.h post.c
	gcc -c server.c
post.o: post.h post.c
	gcc -c post.c
server: server.o post.o
	gcc server.o post.o -o server -lcurl