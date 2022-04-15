EXEC = AsciiArtTool
CC = gcc
OBJS = RLEList.o AsciiArt.o main.o
CFLAGS = gcc -std=c99 -o AsciiArtTool -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors - \
Werror -DNDEBUG *.c tool/*.c

$(EXEC) : $(OBJS)
		$(CC) $(OBJS) -o $@

RLEList.o: RLEList.c RLEList.h
AsciiArt.o: AsciiArt.c AsciiArt.h RLEList.h
main.o: main.c AsciiArt.h

clean:
	rm -f $(OBJS) $(EXEC)