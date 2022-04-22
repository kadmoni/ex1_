#include "RLEList.h"
#include <stdlib.h>

struct RLEList_t
{
    char letter;
    int times;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList list=malloc(sizeof(*list));
    if (list==NULL)
    {
        return NULL;
    }
    *list.letter = "\0";
    *list.times = 0;
    *list.next = NULL;
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
    if ((*list.letter == '\0') || (*list.times == NULL)||(list == NULL)||(value=='\0'))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (value == *list.letter)
    {
        *list.times+=1;
    }
    else
    {
        *list.next= RLEListCreate();
        if (*list.next == NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        **list.next.letter = value;
        **list.next.times = 1;
        return RLE_LIST_SUCCESS;
    }
}


int RLEListSize(RLEList list)
{
    int count = 0;
    while (list){
        count += *list.times;
        list = *list.next;
    }
    return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    *result = RLEListOfIndex(list, index);
    if (result == RLE_LIST_SUCCESS)
    {
        return *list.letter;)
    }
    return 0;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    RLEListResult currentResult = RLEListOfIndex(list, index);
    if (*list.times == 1){
        *list.next = **list.next.next;
        *list.times = **list.next.times;
        *list.letter = **list.next.letter;
        list = *list.next;
        free(list);
    }
    else {
        *list.times -= 1;
    }
}


RLEListResult RLEListOfIndex(RLEList list, int index)
{
    if ((*list.letter == '\0') || (*list.times == NULL)||(list == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    int temp = *list.times;
    while (index){
        index -= 1;
        if (index == 0){
            return RLE_LIST_SUCCESS;
        }
        temp -= 1;
        if (temp == 0) {
            if (*list.next == NULL) {
                return RLE_LIST_INDEX_OUT_OF_BOUNDS;
            }
            list = *list.next;
            temp = *list.times;
        }
    }
}

//implement the functions here
