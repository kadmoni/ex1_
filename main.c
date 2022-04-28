#include <stdio.h>
#include "RLEList.h"
#include "AsciiArtTool.h"


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
        
    }

    if (argv[0] == '-i')
    {
        RLEList header = asciiArtPrint(input);
        RLEList ptr = header;
        while (ptr != NULL)
        {
            if (ptr->letter == ' ')
            {
                ptr->letter = '@';
            }
        }
        asciiArtPrint(header,output);
    }
}
