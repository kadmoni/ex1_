#include "RLEList.h"
#include <stdlib.h>

#define NODE_INFO 3
#define EMPTY_POINTER -1
#define ZERO 0
#define ONE 1
#define DECIMAL_BASE 10
#define FIRST_LETTER 1


struct RLEList_t{
    char letter;
    int times;
    struct RLEList_t* next;
};

void RLEListNodeJoin(RLEList list);


RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if (list==NULL)
    {
        free(list);
        return NULL;
    }
    list->letter = '\0';
    list->times = ZERO;
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
    if (list->times == ZERO)
    {
     	list->letter = value;
        list->times = FIRST_LETTER;
        return RLE_LIST_SUCCESS;
    }
    

    while (list->next)
    {
        if (list->next->times == ZERO)
        {
            RLEListDestroy(list->next);
            break;
        }
     	list = list->next;
    }

    if (value == list->letter)
    {
        (list->times)++;
        return RLE_LIST_SUCCESS;
    }

    list->next = RLEListCreate();
    if (list->next == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    list = list->next;

    list->letter = value;
    list->times = FIRST_LETTER;
    list->next = NULL;
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
        count = count + list->times;
    }
    return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (index<ZERO)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return ZERO;
    }
    if ((list != NULL)&&(list->times > ZERO))
    {
        if (index == ZERO)
        {
            if (result != NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return list->letter;
        }
        while (list != NULL)
        {
            for (int count = ZERO; count<list->times;count++)
            {
                if (index == ZERO)
                {
                    if (result != NULL)
                    {
                        *result = RLE_LIST_SUCCESS;
                    }
                    return list->letter;
                }
                index--;
            }
            list = list->next;
        }
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return ZERO;
    }
    else if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return ZERO;
    }
    else
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return ZERO;
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    RLEList header = list;
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (list->times == ZERO)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    index++;
    while(list != NULL)
    {
        for (int counter = list->times; counter > ZERO;counter--)
        {
            index--;
            if (index == ZERO)
            {
                break;
            }
        }
        if (index == ZERO)
        {
            break;
        }
        list=list->next;
    }
    if (list == NULL)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    if (list->next == NULL)
    {
        if (list->times == FIRST_LETTER)
        {
            list->times = ZERO;
            list->letter = '\0';
            list->next = NULL;
            return RLE_LIST_SUCCESS;
        }
        else {
            (list->times)--;
        }
    }
    else if (list->times == FIRST_LETTER)
    {
        RLEList listToFree = list->next;
        list->times = list->next->times;
        list->letter = list->next->letter;
        list->next = list->next->next;
        free(listToFree);
        RLEListNodeJoin(header);
        return RLE_LIST_SUCCESS;
    }
    else {
        (list->times)--;
        return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
            return NULL;
        }
    }

    RLEList listPointer = list;
    int nodeCount = ZERO;
    int addToString = ZERO;
    int listTimes;

    while (listPointer)
    {
        listTimes = listPointer->times;
        while (listTimes >= DECIMAL_BASE)
        {
            addToString++;
            listTimes = listTimes/DECIMAL_BASE;
        }
        nodeCount++;
        listPointer = listPointer->next;
    }
    char *string = malloc(sizeof(char)*nodeCount*NODE_INFO+addToString+ONE);
    if (!string)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
    }
    for (int i = ZERO; i<nodeCount*NODE_INFO+addToString+ONE;i++ )
    {
        *(string+i) = '\0';
    }
    int stringIndex = ZERO;
    do
    {
        *(string+stringIndex++) = list->letter;
        listTimes=list->times;
        int power = ZERO;
        while (listTimes >= DECIMAL_BASE)
        {
            power++;
            listTimes = listTimes/DECIMAL_BASE;
        }
        while(power>=ZERO)
        {
            int tempPower = power;
            int devision = ONE;
            for ( ; tempPower > ZERO; tempPower--)
                {
                    devision = devision * DECIMAL_BASE;
                }
            *(string + stringIndex++) = ((list->times/devision)%DECIMAL_BASE) + '0';
            power--;
        }
        *(string+stringIndex++) = '\n';
	    list = list->next;
    } while(list);
    if (stringIndex == NODE_INFO*nodeCount+addToString)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_SUCCESS;
        }
    }
    if (result != NULL)
    {
        if (*result != RLE_LIST_SUCCESS)
        {
            free(string);
            return NULL;
        }
    }
    return string;
}



RLEListResult RLEListMap (RLEList list, MapFunction map_function)
{
    RLEList Header = list;
    char temp;
    if ((list==NULL) || (map_function == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list != NULL)
    {
        temp = map_function(list->letter);
        list->letter = temp;
        list = list->next;
    }
    RLEListNodeJoin(Header);
    return RLE_LIST_SUCCESS;
}

void RLEListNodeJoin(RLEList list)
{
    
    if (list->next == NULL)
    {
        return;
    }
    
    int repetition = false;
    char nextLetter = list->next->letter;
    
    while(list->next)
    {
        if (list->letter == nextLetter)
        {
            repetition = true;
            break;
        }
        list = list->next;
        if (list->next == NULL)
        {
            return;
        }
        nextLetter = list->next->letter;
    }
    if (repetition)
    {
        RLEList listToFree = list->next;
        list->times = (list->times) + (list->next->times);
        list->next = list->next->next;
        free(listToFree);
        RLEListNodeJoin(list);
        return;
    }
    else
    {
        return;
    }
}

