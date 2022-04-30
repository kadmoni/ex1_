prog: AsciiArtTool.o main.o RLEList.o
	gcc AsciiArtTool.o main.o RLEList.o -o prog

AsciiArtTool.o: AsciiArtTool.c RLEList.h AsciiArtTool.h
	gcc -std=c99 -c AsciiArtTool.c

main.o: main.c RLEList.h AsciiArtTool.h
	gcc -c main.c

RLEList.o: RLEList.c RLEList.h
	gcc -c  RLEList.c
