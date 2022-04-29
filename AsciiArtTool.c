#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>

#define NODE_INFO 3
#define EMPTY_POINTER -1
#define BUFFER_SIZE 2
#define BUFFER_SIZE2 4
#define NUMBER 1
#define LETTER 0

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
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result;
    char buffer [BUFFER_SIZE2] = "";
    char* encodedStringTemp = fgets(buffer,BUFFER_SIZE2,RLEListExportToString(list,result));
    while(encodedStringTemp!=NULL)
    {
        for (int count = (int)encodedStringTemp[NUMBER];count>0;count--)
        {
            fputs(encodedStringTemp[LETTER],out_stream);
        }
        encodedStringTemp = fgets(buffer,BUFFER_SIZE2,RLEListExportToString(list,result));
    }
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