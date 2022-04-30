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
    printf("now in ascii art read \n");
    RLEList header = RLEListCreate();
    RLEList ptr = header;
    char buffer [BUFFER_SIZE] = "";
    while (fgets(buffer,BUFFER_SIZE,in_stream) != NULL)
    {
        RLEListAppend(ptr,buffer[0]);
    }
    printf("/////////////////////////////////////////////////////////");
    return header;
}

//prints given list to file (not encoded)
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    int listSize = RLEListSize(list);
    int index = 0;
    RLEListResult result;
    while (index < listSize)
    {
	char currentLetter[2] ="";
	currentLetter[0] = RLEListGet(list,index, &result); 
        fputs(currentLetter,out_stream);
        index++;
    }
    RLEListDestroy(list);
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
    /*int indexOfEncoded = 0;
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
    printf("now in ascii art print encoded \n");
    RLEListResult result;
    if ((list == NULL)||(out_stream==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (fputs(RLEListExportToString(list,&result),out_stream) == EOF)
    {
        RLEListDestroy(list);
        return RLE_LIST_ERROR;
    }
    else
    {
        RLEListDestroy(list);
        return RLE_LIST_SUCCESS;
    }
}
