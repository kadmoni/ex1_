#include <stdio.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define BUFFER_SIZE 2


int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Problem: copy <file1> <file2>", NULL);
        return 0;
    }
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("Error: cannot open", argv[1]);
        return 0;
    }
    FILE *output = fopen(argv[2], "w");
    if (!output) {
        fclose(input);
        printf("Error: cannot open", argv[2]);
        return 0;
    }

    if (argv[0] == '-e')
    {
        RLEList header = asciiArtRead(input);
        RLEListResult result = asciiArtPrintEncoded(header, output);
        if (result != RLE_LIST_SUCCESS)
        {
            printf("Error encoding ascii art");
        }
    }

    if (argv[0] == '-i')
    {
        char buffer [BUFFER_SIZE] = "";
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
    }
}
