#include "RLEList.h"
#include <stdlib.h>


#define NODE_INFO 3
#define EMPTY_POINTER -1

RLEListResult RLEListOfIndex(RLEList list, int index);
int RLENodeNumber(RLEList list);

struct RLEList_t{
    char letter;
    int times;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if (list==NULL)
    {
        return NULL;
    }
    list->letter = '\0';
    list->times = 0;
    list->next = NULL;
    return list;
}

void RLEListDestroy(RLEList list) {
    while(list) {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEListResult RLEListAppend (RLEList list, char value)
{
    if ((!list) || (value == '\0'))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if ((list->times == 0)||(list->letter == '\0'))
    {
     	list->letter = value;
        list->times = 1;
        return RLE_LIST_SUCCESS;
    }
    

    while (list->next)
    {
     	list = list->next;
    }

    if (value == list->letter)
    {
        list->times++;
        return RLE_LIST_SUCCESS;
    }

    list->next = RLEListCreate();
    if (list->next == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    list->next->letter = value;
    list->next->times = 1;
    list->next->next = NULL;
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return EMPTY_POINTER;
    }

    int count = list->times;
    while (list->next)
    {
        list = list->next;
        count += list->times;
    }
    return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    *result = RLE_LIST_SUCCESS;
    while(list != NULL)
    {
        for (int counter = list->times; counter>0;counter--)
        {
            index--;
            if (index == 0)
            {
                break;
            }
        }
        if (index == 0)
        {
            break;
        }
        list=list->next;
    }
    if (list == NULL)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return '0';
    }
    return list->letter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    RLEList tempPointer = list;
    while(tempPointer != NULL)
    {
        for (int counter = tempPointer->times; counter>0;counter--)
        {
            index--;
            if (index == 0)
            {
                break;
            }
        }
        if (index == 0)
        {
            break;
        }
        tempPointer=tempPointer->next;
    }
    if (tempPointer == NULL)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

//   // RLEListResult currentResult = RLEListOfIndex(tempPointer, index);
//    if (currentResult != RLE_LIST_SUCCESS)
//    {
//        return currentResult;
//    }
    if (tempPointer->next == NULL)
    {
        if (tempPointer->times == 1)
        {
            RLEListDestroy(tempPointer);
        }
        else {
            (tempPointer->times)--;
        }
    }
    else if (tempPointer->times == 1)
    {
        tempPointer->next = tempPointer->next->next;
        tempPointer->times = tempPointer->next->times;
        tempPointer->letter = tempPointer->next->letter;
        if (tempPointer == list)
	    {
            return RLE_LIST_ERROR;
	    }
        free(tempPointer->next);
        return RLE_LIST_SUCCESS;
    }
    else {
        (tempPointer->times)--;
        return RLE_LIST_SUCCESS;
    }

    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    int nodeCount = RLENodeNumber(list);
    char *string = malloc(sizeof(char)*nodeCount*NODE_INFO+1);
    if (!string)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;
    }
    for (int i=0;i<nodeCount*NODE_INFO+1;i++)
    {
        *(string+i)='\0';
    }
    int stringIndex = 0;
    do {
        *(string+stringIndex) = list->letter;
        stringIndex++;
        *(string+stringIndex) = list->times + '0';
        stringIndex++;
        *(string+stringIndex) = '\n';
        stringIndex++;
	list = list->next;
    } while(list);

    if (stringIndex == NODE_INFO*nodeCount){
        *result = RLE_LIST_SUCCESS;
    }

    if (*result != RLE_LIST_SUCCESS)
    {
        return NULL;
    }
    return string;
}

int RLENodeNumber(RLEList list)
{
    int nodeCount = 1;
    while (list->next)
    {
        nodeCount++;
        list = list->next;
    }
    return nodeCount;
}

RLEListResult RLEListMap (RLEList list, MapFunction map_function) // changes the letters in node according to mapfunction
{
    char temp;
    if ((list==NULL) || (map_function == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list != NULL)
    {
        temp = map_function(list->letter);
        lisr->letter = temp;
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}

