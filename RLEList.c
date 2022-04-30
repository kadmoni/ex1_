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
    printf("now in createlist \n"); 
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
    printf("now in append function \n");
    if ((!list) || (value == '\0'))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    printf("append: not null1 parameteres 1 \n");
    if ((list->times == 0)||(list->letter == '\0'))
    {
     	list->letter = value;
        list->times = 1;
        return RLE_LIST_SUCCESS;
    }
    
    RLEList tempPointer = list;
    printf("append function also not first node 2 \n");
    
    while (tempPointer->next)
    {
     	tempPointer = tempPointer->next;
    }
    printf("appened getting to last mode 3 \n");
    if (value == tempPointer->letter)
    {
        tempPointer->times++;
        return RLE_LIST_SUCCESS;
    }

    printf("check if last node has same character \n");
    tempPointer->next = RLEListCreate();
    if (tempPointer->next == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    tempPointer->next->letter = value;
    tempPointer->next->times = 1;
    tempPointer->next->next = NULL;
    printf("append: set new last node function5 \n");
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
    RLEList tempPointer = list;
    *result = RLEListOfIndex(tempPointer, index);
    if (*result != RLE_LIST_SUCCESS)
    {
        return 0;
    }
    return tempPointer->letter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    RLEList tempPointer = list;
    RLEListResult currentResult = RLEListOfIndex(tempPointer, index);
    if (currentResult != RLE_LIST_SUCCESS)
    {
        return currentResult;
    }

    if (tempPointer->times == 1)
    {
        tempPointer->next = tempPointer->next->next;
        tempPointer->times = tempPointer->next->times;
        tempPointer->letter = tempPointer->next->letter;
        if (tempPointer == list)
	    {
	        list = list->next;
	    }
        tempPointer = tempPointer->next;  
        free(tempPointer);
    }
    else {
        tempPointer->times--;
    }

    return currentResult;
}


RLEListResult RLEListOfIndex(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int temp = list->times;
    if (index == 0)
    {
        return RLE_LIST_SUCCESS;
    }
    do {
        index--;
        if (index == 0){
            return RLE_LIST_SUCCESS;
        }
        temp--;
        if (temp == 0) {
            if (list->next == NULL) {
                return RLE_LIST_INDEX_OUT_OF_BOUNDS;
            }
            list = list->next;
            temp = list->times;
        }
    } while (index);
    return RLE_LIST_ERROR;
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
    printf("now in export to string, this is our current string after export: \n%s", string);
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
    RLEList temp = list; // pointer to the current node being worked on
    if ((!list) || (map_function == '\0'))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (temp != NULL)
    {
        if (list->letter == 'c')
        {
            char temp = map_function(list->letter);
            list->letter = temp;
        }
        ptr = list->next;
    }
    return RLE_LIST_SUCCESS;
}
