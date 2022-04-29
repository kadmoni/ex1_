prog: AsciiArtTool.o main.o RLEList.o
	gcc AsciiArtTool.o main.o RLEList.o -o prog

AsciiArtTool.o: AsciiArtTool.c RLEList.h AsciiArtTool.h
	gcc -std=c99 -g -c AsciiArtTool.c

main.o: main.c RLEList.h AsciiArtTool.h
	gcc -g -c main.c

RLEList.o: RLEList.c RLEList.h
	gcc -g -c  RLEList.c
