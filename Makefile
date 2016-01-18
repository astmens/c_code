CC = gcc

#Recommended flags:
CFLAGS1 = -Wall -pedantic -std=c99
#CFLAGS2 = -Wtraditional -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion 
CFLAGS2 = -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion
DEBUGFLAG = -g

DEPS = object.o

CFLAGS = $(DEBUGFLAG) $(CFLAGS1) $(CFLAGS2)

SRCS = $(wildcard ex*.c )
EXES = $(SRCS:.c=)

all: $(EXES) $(DEPS) 

deps: $(DEPS) 

# extra line for ex19, to add its specific dependencies:
ex19: ex19.c object.o

%:	%.c
	$(CC) $^ -o $@ $(CFLAGS)
	
#	$(CC) $< -o $@ $(CFLAGS) $(CFLAGS2) $(DEBUGFALG)

clean:
	rm -f $(EXES) *~ *.o

list:
	echo $(SRCS)

.Phony: clean list

