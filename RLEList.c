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
    if (value == list->letter)
    {
        list->times+=1;
        return RLE_LIST_SUCCESS;
    }
    if ((list->times == 0)&&(list->letter == '\0'))
    {
        list->letter = value;
        list->times = 1;
        return RLE_LIST_SUCCESS;
    }

    while (list->next)
    {
        list = list->next;
    }
    list->next= RLEListCreate();
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
    *result = RLEListOfIndex(list, index);
    if (result != RLE_LIST_SUCCESS)
    {
        return 0;
    }
    return list->letter;)
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    RLEListResult currentResult = RLEListOfIndex(list, index);
    if (currentResult != RLE_LIST_SUCCESS)
    {
        return currentResult;
    }

    if (*list.times == 1){
        list->next = list->next->next;
        list->times = list->next->times;
        list->letter = list->next->letter;
        list = list->next;
        free(list);
    }
    else {
        list->times -= 1;
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
    while (index){
        index -= 1;
        if (index == 0){
            return RLE_LIST_SUCCESS;
        }
        temp -= 1;
        if (temp == 0) {
            if (list->next == NULL) {
                return RLE_LIST_INDEX_OUT_OF_BOUNDS;
            }
            list = list->next;
            temp = list->times;
        }
    }
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT
    }

    int nodeCount = RLENodeNumber(list);

    char *string = malloc(sizeof(char)*nodeCount*NODE_INFO);

    int stringIndex = 0;
    do {
        *(string+stringIndex) = test->letter;
        stringIndex++;
        *(string+stringIndex) = test->times + '0';
        stringIndex++;
        *(string+stringIndex) = '\n';
        stringIndex++;
        list = list->next;
    } while(list->next);

    if (stringIndex == NODE_INFO*nodeCount){
        *result = LIST_SUCCESS;
    }

    if (*result != LIST_SUCCESS)
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
        nodeCount++
        list = list->next;
    }
    return nodeCount;
}

void RLEListMap (RLEList list, MapFunction map_function) // changes the letters in node according to mapfunction
{
    RLEList ptr = list; // pointer to the current node being worked on
    while (ptr != NULL)
    {
        if (list->letter == 'c')
        {
            char temp = map_function(list->letter);
            list->letter = temp;
        }
        ptr = list->next;
    }
}