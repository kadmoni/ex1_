#include "RLEList.h"
#include "AsciiArtTool.h"
#include <stdlib.h>

#define NODE_INFO 3
#define EMPTY_POINTER -1
#define BUFFER_SIZE 2
#define BUFFER_SIZE2 4
#define NUMBER 1
#define LETTER 0

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEList asciiArtRead(FILE* in_stream)
{
    printf("now in ascii art read \n");
    RLEList header = RLEListCreate();
    FILE* file;
    file = fopen("/home/adi.tsach/ex1_/2out.txt", "w");
    RLEList ptr = header;
    char buffer [BUFFER_SIZE] = "";
    while (fgets(buffer,BUFFER_SIZE,in_stream) != NULL)
    {
        RLEListAppend(ptr,buffer[0]);
    }
//    asciiArtPrint(header, file);
    return header;
}

//prints given list to file (not encoded)
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    printf("now in ascii art print function \n");
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult* result;

    int sizeNode = RLEListSize(list);

    char* stringEncoded = RLEListExportToString(list,result);
    char* stringNotEncoded = malloc(sizeof(char)* sizeNode);
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

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    printf("now in ascii art print encoded \n");
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
