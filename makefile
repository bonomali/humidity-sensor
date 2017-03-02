#TODO: Run dep-linux case is LINUX and lib is not installed 

BUILDDIR = server
BINDIR = bin
CC=gcc

# Install dependencies when running on linux
dep-linux:
	sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get install libcurl4-gnutls-dev

# Clean binary files.
clean:
	rm -rf $(BINDIR)
	rm $(BUILDDIR)/*.o

server.o: $(BUILDDIR)/*.c $(BUILDDIR)/*.h
	$(CC) -c $(BUILDDIR)/server.c
post.o: $(BUILDDIR)/post.*
	$(CC) -c $(BUILDDIR)/post.c
systools.o: $(BUILDDIR)/systools.*
	$(CC) -c $(BUILDDIR)/systools.c
server: $(BUILDDIR)/server.o $(BUILDDIR)/post.o $(BUILDDIR)/systools.o
	mkdir -p $(BINDIR)
	$(CC) $(BUILDDIR)/*.o -o $(BINDIR)/server -lcurl