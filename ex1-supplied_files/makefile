EXEC = prog
CC = gcc
OBJS = RLEList.o AsciiArt.o
CFLAGS =  -std=c99 -Wall -pedantic-errors -Werror
TEST_PATH = tests
TEST_RLELIST = RLEList_example_test.o

$(EXEC) : $(OBJS)
		$(CC) $(OBJS) -o $@

RLEList.o: RLEList.c RLEList.h
AsciiArt.o: AsciiArt.c AsciiArt.h RLEList.h

clean:
	rm -f $(OBJS) $(EXEC)