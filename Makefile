CC = gcc

#Recommended flags:
CFLAGS1 = -Wall -pedantic -std=c99
#CFLAGS2 = -Wtraditional -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion 
CFLAGS2 = -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion
DEBUGFLAG = -g

DEPS = object.o ex22_funcs.o libex29.o

SOLIB = libex29.so

CFLAGS = $(DEBUGFLAG) $(CFLAGS1) $(CFLAGS2)

#SRCS = $(wildcard ex*.c )
SRCS = $(wildcard ex*[!s].c ) # excludes names like exXX_funcs.c
EXES = $(SRCS:.c=)

all: $(EXES) $(DEPS) $(SOLIB)

deps: $(DEPS) 

# extra line for ex19, to add its specific dependencies:
ex19: ex19.c object.o

ex22_main: ex22_main.c ex22_funcs.o

ex29: ex29.c libex29.so

# need extra flag -fPIC, therfore seperate rule:
libex29.o: libex29.c
	$(CC) -c -o $@ $^ -fPIC $(CFLAGS)
# need extra flag -ldl:
ex29: ex29.c libex29.so Makefile
	$(CC) -o $@ $< -ldl $(CFLAGS)

# creating shared library: (as in Exercise 29)
%.so: %.o
	$(CC) -shared -o $@ $^ $(CFLAGS)


%:	%.c
	$(CC) $^ -o $@ $(CFLAGS)
	
#	$(CC) $< -o $@ $(CFLAGS) $(CFLAGS2) $(DEBUGFALG)



clean:
	rm -f $(EXES) *~ *.o

list:
	echo $(SRCS)

.Phony: clean list

