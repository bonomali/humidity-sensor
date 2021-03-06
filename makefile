BUILDDIR = server
BINDIR = bin
CC=gcc
CFLAGS= -g
SYSTOOLS = $(BUILDDIR)/systools.h

# Install dependencies when running on linux
dep-linux:
	sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get install libcurl4-gnutls-dev
	sudo apt-get install libconfig-dev

# Clean binary files.
clean:
	rm -rf $(BINDIR)
	rm $(BUILDDIR)/*.o

server.o: $(BUILDDIR)/*.c $(BUILDDIR)/*.h
	$(CC) $(CFLAGS) -c $(BUILDDIR)/server.c
post.o: $(BUILDDIR)/post.* $(SYSTOOLS)
	$(CC) $(CFLAGS) -c $(BUILDDIR)/post.c
watering.o: $(BUILDDIR)/watering.* $(SYSTOOLS)
	$(CC) $(CFLAGS) -c $(BUILDDIR)/watering.c
regex.o: $(BUILDDIR)/regex.* $(SYSTOOLS)
	$(CC) $(CFLAGS) -c $(BUILDDIR)/regex.c
bluetooth.o: $(BUILDDIR)/bluetooth.* $(SYSTOOLS)
	$(CC) $(CFLAGS) -c $(BUILDDIR)/bluetooth.c
config.o: $(BUILDDIR)/config.* $(SYSTOOLS)
	$(CC) $(CFLAGS) -c $(BUILDDIR)/config.c
systools.o: $(BUILDDIR)/systools.* $(BUILDDIR)/post.h $(BUILDDIR)/config.h
	$(CC) $(CFLAGS) -c $(BUILDDIR)/systools.c
server: $(BUILDDIR)/server.o $(BUILDDIR)/post.o $(BUILDDIR)/watering.o $(BUILDDIR)/systools.o $(BUILDDIR)/regex.o $(BUILDDIR)/bluetooth.o $(BUILDDIR)/config.o
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(BUILDDIR)/*.o -o $(BINDIR)/server -lconfig -lcurl
