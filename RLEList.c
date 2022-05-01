#include "RLEList.h"
#include <stdlib.h>
#include <string.h>


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
    
    RLEList tempPointer = list;
    
    while (tempPointer->next)
    {
     	tempPointer = tempPointer->next;
    }

    if (value == tempPointer->letter)
    {
        tempPointer->times++;
        return RLE_LIST_SUCCESS;
    }

    tempPointer->next = RLEListCreate();
    if (tempPointer->next == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    tempPointer->next->letter = value;
    tempPointer->next->times = 1;
    tempPointer->next->next = NULL;
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return EMPTY_POINTER;
    }
    RLEList tempPointer = list;
    int count = tempPointer->times;
    while (tempPointer->next)
    {
        tempPointer = tempPointer->next;
        count += tempPointer->times;
    }
    return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    *result = RLE_LIST_SUCCESS;
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
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return '0';
    }
    return tempPointer->letter;
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


RLEListResult RLEListOfIndex(RLEList list, int index)
{
    while(list->next!=NULL)
        {
        for (int counter = list->times; counter>0;counter--)
        {
            index--;
            if (index == 0)
            {
                return RLE_LIST_SUCCESS;
            }
        }
        list=list->next;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS; // change the retrun value and placement (maybe)
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    int nodeCount = RLENodeNumber(list);
    char *string = malloc(sizeof(char)*nodeCount*NODE_INFO);
    if (!string)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;
    }
    RLEList tempPointer	= list;
    int stringIndex = 0;
    do {
        *(string+stringIndex) = tempPointer->letter;
        stringIndex++;
        *(string+stringIndex) = tempPointer->times + '0';
        stringIndex++;
        *(string+stringIndex) = '\n';
        stringIndex++;
	tempPointer = tempPointer->next;
    } while(tempPointer);

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
    RLEList tempPointer = list;
    while (tempPointer->next)
    {
        nodeCount++;
        tempPointer = tempPointer->next;
    }
    return nodeCount;
}

RLEListResult RLEListMap (RLEList list, MapFunction map_function) // changes the letters in node according to mapfunction
{
    RLEList ptr = list; // pointer to the current node being worked on
    char temp;
    if ((ptr==NULL) || (map_function == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (ptr != NULL)
    {
        temp = map_function(ptr->letter);
        ptr->letter = temp;
        ptr = ptr->next;
    }
    return RLE_LIST_SUCCESS;
}

