#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define BUFFER_SIZE 2

char invertMapping (char toInvert);


int main(int argc, char** argv) {

    if (argc != 4) {
        printf("Problem: unexpected number of arguments received %d",argc);
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
    
    if (!strcmp(argv[1],"-e"))
    {
	    RLEList header = asciiArtRead(input);
        RLEListResult result = asciiArtPrintEncoded(header, output);
        if (result != RLE_LIST_SUCCESS)
        {
            printf("Error encoding ascii art");
        }
    }

    if (!strcmp(argv[1],"-i"))
    {
	    RLEList header = asciiArtRead(input);
	    RLEListMap(header, &invertMapping);
        asciiArtPrint(header, output);
    }
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
