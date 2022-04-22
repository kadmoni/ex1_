#include "RLEList.h"

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

RLEListResult RLEListRemove (RLEList list, int index)
{
    if ((*list.letter == '\0') || (*list.times == NULL)||(list == NULL)||(value=='\0'))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (RLEListSize(list)<index)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else
    {

    }
}

//implement the functions here