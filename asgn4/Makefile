# Makefile for CSE 13S, Spring 2023, Assignment 4


CC=clang
debug:   CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -gdwarf-4
release: CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS=-lm

EXECBIN=tsp
OBJS=\
    stack.o \
    graph.o \
    path.o \
    tsp.o \


.PHONY: all debug release clean

all: debug

debug: $(EXECBIN)

release: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i --style=file *.[ch]
