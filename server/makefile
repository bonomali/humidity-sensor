dep-linux:
	sudo apt-get install libcurl4-gnutls-dev
server.o: server.c post.h post.c systools.h systools.c
	gcc -c server.c
post.o: post.h post.c
	gcc -c post.c
systools.o: systools.h systools.c
	gcc -c systools.c
server: server.o post.o systools.o
	gcc server.o post.o systools.o -o server -lcurl