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
void RLEListDestroy (RLEList list)
{
    free(list);
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
    if ((*list.letter == '\0') || (*list.times == NULL)||(list == NULL))
    {
        result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }

    int temp = *list.times;
    while (index){
        index -= 1;
        if (index == 0){
            result = RLE_LIST_SUCCESS;
            return *list->letter;
        }
        temp - 1;
        if (temp == 0) {
            if (*list.next == NULL) {
                result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
                return 0;
            }
            list = *list.next;
            temp = *list.times;
        }
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
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
        temp - 1;
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
