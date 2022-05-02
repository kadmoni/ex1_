#include "RLEList.h"
#include <stdlib.h>


#define NODE_INFO 3
#define EMPTY_POINTER -1

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
        free(list);
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
    if (list->times == 0)
    {
     	list->letter = value;
        list->times = 1;
        return RLE_LIST_SUCCESS;
    }
    

    while (list->next)
    {
        if (list->next->times == 0)
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
    list->times = 1;
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
    if (index<0)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    if ((list != NULL)&&(list->times > 0))
    {
        if (index == 0)
        {
            if (result != NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return list->letter;
        }
        while (list != NULL)
        {
            for (int count = 0; count<list->times;count++)
            {
                if (index == 0)
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
        return 0;
    }
    else if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    else
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
}
    /*
    index++;
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if ( index == 1 )
    {
        return list->letter;
    }
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
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return list->letter;
}*/

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (list->times == 0) // not clear what to do in index 1
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    index++;
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
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

//   // RLEListResult currentResult = RLEListOfIndex(tempPointer, index);
//    if (currentResult != RLE_LIST_SUCCESS)
//    {
//        return currentResult;
//    }
    if (list->next == NULL)
    {
        if (list->times == 1)
        {
            list->times = 0;
            list->letter = '\0';
            list->next = NULL;
            //RLEListDestroy(list);
            return RLE_LIST_SUCCESS;
        }
        else {
            (list->times)--;
        }
    }
    else if (list->times == 1)
    {
        RLEList tempPointer = list->next;
        list->times = list->next->times;
        list->letter = list->next->letter;
        list->next = list->next->next;
        free(tempPointer);
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

    RLEList tempPointer = list;
    int nodeCount = 1;
    int addToString = 0;
    int tempTimes;
    while (tempPointer->next)
    {
        tempTimes = tempPointer->times;
        while (tempTimes >= 10)
        {
            addToString++;
            tempTimes = tempTimes/10;
        }
        nodeCount++;
        tempPointer = tempPointer->next;
    }
    char *string = malloc(sizeof(char)*nodeCount*NODE_INFO+addToString+1);
    if (!string)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
    }
    for (int i = 0; i<nodeCount*NODE_INFO+addToString+1;i++ )
    {
        *(string+i) = '\0';
    }
    int stringIndex = 0;
    do
    {
        *(string+stringIndex) = list->letter;
        stringIndex++;
        tempTimes=list->times;
        int power = 0;
        while (tempTimes >= 10)
        {
            power++;
            tempTimes = tempTimes/10;
        }
        while(power>=0)
        {
            int tempPower = power;
            int devision = 1;
            for ( ; tempPower > 0; tempPower--)
                {
                    devision = devision * 10;
                }
            *(string + stringIndex) = ((list->times/devision)%10) + '0';
            power--;
            stringIndex++;
        }
        *(string+stringIndex) = '\n';
        stringIndex++;
	    list = list->next;
    } while(list);
    //string[nodeCount*NODE_INFO+addToString] = '\0';
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
        list->letter = temp;
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}

