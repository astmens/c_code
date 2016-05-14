PREFIX?=/usr/local
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1 -I${PREFIX}/apr/include/apr-util-1
LDFLAGS=-L${PREFIX}/apr/lib 
# LDFLAGS=-L${PREFIX}/apr/lib -L .aprutil-1 -L .apr-1
# Don't add libraries (-lfoo) to LDFLAGS. They must come after all the objects are listed, with most UNIX linkers which are single-pass linkers. GNU make's default variables use LDFLAGS to hold linker flags like -Lfoodir and LDLIBS to hold libraries like -lfoo. 
LDLIBS= -lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o commands.o

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin
	
clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM

