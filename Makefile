CC = gcc

#Recommended flags:
CFLAGS = -Wall -pedantic -std=c99
#CFLAGS2 = -Wtraditional -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion 
CFLAGS2 = -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion
DEBUGFLG = -g
DEPS = 

SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=)

all: $(EXES)


%:	%.c $(DEPS)
	$(CC) $< -o $@ $(CFLAGS) $(CFLAGS2) $(DEBUGFLG)

clean:
	rm -f $(EXES)

.Phony: clean
