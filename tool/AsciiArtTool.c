#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>
#include <stdio.h>

#define EMPTY_POINTER -1
#define BUFFER_SIZE 2
#define ZERO 0
#define SINGLE_CHAR_ARRAY 2



RLEList asciiArtRead(FILE* in_stream)
{
    RLEList header = RLEListCreate();
    RLEList ptr = header;
    char buffer [BUFFER_SIZE] = "";
    while (fgets(buffer,BUFFER_SIZE,in_stream) != NULL)
    {
        RLEListAppend(ptr,buffer[ZERO]);
    }
    return header;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    int listSize = RLEListSize(list);
    RLEListResult result;
    for (int index = ZERO;index<listSize;index++)
    {
        char array [SINGLE_CHAR_ARRAY]= {ZERO};
        array[0] = RLEListGet(list,index,&result);
        array[1] = '\0';
        fputs(array,out_stream);
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
    char* string = RLEListExportToString(list,&result);
    if (string ==NULL)
    {
        return RLE_LIST_ERROR;
    }
    if (fputs(string,out_stream) == EOF)
    {
        free(string);
        return RLE_LIST_ERROR;
    }
    else
    {
        free(string);
        return RLE_LIST_SUCCESS;
    }
}
