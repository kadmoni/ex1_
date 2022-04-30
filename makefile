AsciiArtTool: AsciiArtTool.o main.o RLEList.o
	gcc -std=c99 -o AsciiArtTool -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c

AsciiArtTool.o: AsciiArtTool.c RLEList.h AsciiArtTool.h
	gcc -std=c99 -c AsciiArtTool.c

main.o: main.c RLEList.h AsciiArtTool.h
	gcc -c main.c

RLEList.o: RLEList.c RLEList.h
	gcc -c  RLEList.c
