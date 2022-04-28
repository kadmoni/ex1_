#include "RLEList.h"
#include <stdlib.h>

#define NODE_INFO 3
#define EMPTY_POINTER -1
#define BUFFER_SIZE 1

// כותבים כל מה שצריך בתוך התוכנית יש להם ifndef בפנים כנגיע ללינקר
//check how to access members of struct RLEList

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList header = RLEListCreate();
    RLEList ptr = header;
    char buffer [BUFFER_SIZE] = "";
    //don't need open, we got the file pointer, probably opened in the calling function.
    fgets(buffer,BUFFER_SIZE,in_stream);//check if buffer size should be +1 of buffer to accommodate \0;
    //check input error (returns NULL)
    header->letter = buffer[0];
    //check if empty
    RLEListAppend(ptr,buffer[0])
    //finish implementation after fixing append (need to decide what happens to list)
    //loop until reaches NULL, return header (not ptr)
}

//prints given list to file (not encoded)
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEList ptr = list; // pointer so header won't change
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (ptr != NULL)
    {
        char toPrint = ptr->letter;
        for (int counter = ptr->times; counter > 0; counter--) // number of times to print char
        {
            if (fputs(&toPrint, out_stream) == EOF)
            {
                return RLE_LIST_ERROR;
            }
        }
        ptr = ptr->next;
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
    if (fputs(RLEListExportToString(list,&result),out_stream) == NULL)
    {
        return RLE_LIST_ERROR;
    }
    else
    {
        return RLE_LIST_SUCCESS;
    }
}