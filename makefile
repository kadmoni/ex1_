AsciiArtTool: AsciiArtTool.o main.o RLEList.o
	gcc -std=c99 -o AsciiArtTool -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c

AsciiArtTool.o: tool/AsciiArtTool.c tool/RLEList.h tool/AsciiArtTool.h
	gcc -std=c99 -c tool/AsciiArtTool.c

main.o: tool/main.c tool/RLEList.h tool/AsciiArtTool.h
	gcc -std=c99 -c ./tool/main.c

RLEList.o: RLEList.c tool/RLEList.h
	gcc -std=c99 -c  RLEList.c
