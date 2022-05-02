#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define ARGUMENTS_NUMBER 4
#define INPUT 2
#define OUTPUT 3
#define FLAG 1
#define ZERO 0




char invertMapping (char toInvert);


int main(int argc, char** argv) {

    if (argc != ARGUMENTS_NUMBER) {
        printf("Problem: unexpected number of arguments received %d",argc);
        return ZERO;
    }

    FILE *input = fopen(argv[INPUT], "r");
    if (input == NULL) {
        printf("Error: cannot open %s", argv[INPUT]);
        return ZERO;
    }
    FILE *output = fopen(argv[OUTPUT], "w");
    if (output == NULL) {
        fclose(input);
        printf("Error: cannot open %s", argv[OUTPUT]);
        return ZERO;
    }
    
    if (!strcmp(argv[FLAG],"-e"))
    {
	    RLEList header = asciiArtRead(input);
        RLEListResult result = asciiArtPrintEncoded(header, output);
        if (result != RLE_LIST_SUCCESS)
        {
            printf("Error encoding ascii art");
        }
    }

    if (!strcmp(argv[FLAG],"-i"))
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
