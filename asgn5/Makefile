CC=clang
debug: CFLAGS=-Wall -Wextra -Werror -Wstrict-prototypes -Werror -pedantic -gdwarf-4
release: CFLAGS=Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LFLAGS=-lm

EXECBIN=colorb
OBJS= \
	colorb.o \
	bmp.o\
	io.o\
	
TESTBIN=iotest
TESTOBJS= \
 	iotest.o\
 	io.o\

.PHONY: all debug release clean

all: debug

debug: $(EXECBIN) $(TESTBIN)

release : $(EXECBIN) $(TESTBIN)

$(EXECBIN): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

$(TESTBIN): $(TESTOBJS)
	$(CC) $(LFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS)
	rm -f $(TESTBIN) $(TESTOBJS)

format: 
	clang-format -i --style=file *.[ch]

scan-build: clean\
	scan-build --use-cc=$(CC) make
