#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>

#define MEMBERS_OF_NODE 3
#define CURRENT_CHAR 0
#define EMPTY_POINTER -1
#define BUFFER_SIZE 2
#define BUFFER_SIZE2 4
#define NUMBER 1
#define LETTER 0

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

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

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEListResult result;
    char* string = RLEListExportToString(list,&result);
    RLEListDestroy(list);
    while (string[0] != '\0')
    {
        for (int counter = (int)(*(string+1)-'0');counter>0;counter--)
        {
            char array [2];
            array[0]= string[0];
            array[1]= '\0';
            fputs(array,out_stream);
        }
        string=string+3;
    }
    free(string);
    return RLE_LIST_SUCCESS;
}
    /*
    printf("now in ascii art print function \n");
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result;
    char* stringEncoded = RLEListExportToString(list,result);
    while (stringEncoded != NULL)
    {
        for (int counter = (int)(stringEncoded[1]-'0');counter > 0; counter--)
        {
            fputs(&stringEncoded[0],out_stream);
        }
        stringEncoded += MEMBERS_OF_NODE;
    }
    int indexOfEncoded = 0;
    int indexOfNotEncoded = 0;
    while(sizeNode>0)
    {
        for(int times = *(stringEncoded+1); times>0; times--)
        {
            *(stringNotEncoded+indexOfNotEncoded) = *(stringEncoded + indexOfEncoded);
            indexOfNotEncoded++;
            sizeNode--;
        }
        indexOfEncoded+=3;
    }
    fputs(stringNotEncoded,out_stream);
    free(stringEncoded);
    free(stringNotEncoded);
    return *result;
}
*/

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
        RLEListDestroy(list);
        return RLE_LIST_ERROR;
    }
    if (fputs(string,out_stream) == EOF)
    {
        free(string);
        RLEListDestroy(list);
        return RLE_LIST_ERROR;
    }
    else
    {
        free(string);
        RLEListDestroy(list);
        return RLE_LIST_SUCCESS;
    }
}
