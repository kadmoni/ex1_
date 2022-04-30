#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define BUFFER_SIZE 2
char invertMapping (char toInvert);

int main(int argc, char** argv) {

    if (argc != 4) {
        printf("Problem: copy <file1> <file2> %d",argc);
        return 0;
    }

    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        printf("Error: cannot open %s", argv[2]);
        return 0;
    }
    FILE *output = fopen(argv[3], "w");
    if (output == NULL) {
        fclose(input);
        printf("Error: cannot open %s", argv[3]);
        return 0;
    }
    
    RLEList header = asciiArtRead(input);
    if (!strcmp(argv[1],"-e"))
    {
        RLEListResult result = asciiArtPrintEncoded(header, output);
        if (result != RLE_LIST_SUCCESS)
        {
            printf("Error encoding ascii art");
        }
    }

    printf("avar if");

    if (!strcmp(argv[1],"-i"))
    {
	printf("passed headerassed headerassed headerassed headerassed headerassed headerassed headerassed headerassed headerassed headerassed header ");
        MapFunction ptr = invertMapping;
	RLEListMap(header, ptr);
        asciiArtPrint(header, output);
    }
        /*char buffer [BUFFER_SIZE] = "";
        char* fileToString = fgets(buffer,BUFFER_SIZE,input);
        while (fileToString != NULL)
        {
            if (fileToString[0] == ' ')
            {
                fileToString[0] = '@';
            }
            fputs(fileToString,output);
            fileToString = fgets(buffer,BUFFER_SIZE,input);
        }
         */
	fclose(input);
   	fclose(output);
}
char invertMapping (char toInvert)
{
    if (toInvert == ' ')
    {
        return '@';
    }
    else
    {
        return toInvert;
    }
}
