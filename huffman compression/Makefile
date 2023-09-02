CC=clang
debug:   CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -gdwarf-4
release: CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS=-lm

all: debug

EXEC1=huff
OBJS1=huff.o bitwriter.o node.o pq.o
LIBS1=io-$(shell uname -m).a
$(EXEC1): $(OBJS1) $(LIBS1)
	$(CC) -o $@ $^

EXEC2=bwtest
OBJS2=bwtest.o bitwriter.o
LIBS2=io-$(shell uname -m).a
$(EXEC2): $(OBJS2) $(LIBS2)
	$(CC) -o $@ $^

EXEC3=nodetest
OBJS3=nodetest.o node.o
LIBS3=io-$(shell uname -m).a
$(EXEC3): $(OBJS3) $(LIBS3)
	$(CC) -o $@ $^

EXEC4=pqtest
OBJS4=pqtest.o pq.o node.o
LIBS4=io-$(shell uname -m).a
$(EXEC4): $(OBJS4) $(LIBS4)
	$(CC) -o $@ $^

.PHONY: all debug release clean

debug: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

release: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC1) $(OBJS1)
	rm -f $(EXEC2) $(OBJS2)
	rm -f $(EXEC3) $(OBJS3)
	rm -f $(EXEC4) $(OBJS4)

format:
	clang-format -i --style=file *.[ch]
