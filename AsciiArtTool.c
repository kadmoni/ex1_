#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>

#define NODE_INFO 3
#define EMPTY_POINTER -1
#define BUFFER_SIZE 2

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList header = RLEListCreate();
    RLEList ptr = header;
    char buffer [BUFFER_SIZE] = "";
    while (fgets(buffer,BUFFER_SIZE,in_stream) != NULL)
    {
        RLEListAppend(ptr,buffer[0]);
    }
    return header;
}

//prints given list to file (not encoded)
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    //RLEList ptr = list; // pointer so header won't change CAN BE CHANGED
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list != NULL)
    {
        char toPrint = list->letter;
        for (int counter = list->times; counter > 0; counter--) // number of times to print char
        {
            if (fputs(&toPrint, out_stream) == EOF)
            {
                return RLE_LIST_ERROR;
            }
        }
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    RLEListResult result;
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (fputs(RLEListExportToString(list,&result),out_stream) == EOF)
    {
        return RLE_LIST_ERROR;
    }
    else
    {
        return RLE_LIST_SUCCESS;
    }
}