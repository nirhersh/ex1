#include "RLEList.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

struct RLEList_t{
    char data;
    struct RLElist_t* next;
};

//implement the functions here

RLEList RLEListCreate()
{
    RLEList list = NULL;
    list = (RLEList)malloc(sizeof(struct RLEList_t)); // what should  i write in the size? now this is the size of a pointer isnt it?
    if(!list)
    {
        return NULL;
    }
    assert(list);
    return list;
}


void RLEListDestroy(RLEList list)
{
    while (list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    } 
}

/**
*   RLEListAppend: add a specified character at the end of the list.
*
* @param list - The RLE list for which to add the character
* @param value - The character which needs to be added.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_OUT_OF_MEMORY if an allocation failed
* 	RLE_LIST_SUCCESS if the character has been inserted successfully
*/
RLEListResult RLEListAppend(RLEList list, char value)
{
    if (value == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    assert(value != NULL);
    list->next = malloc(sizeof(struct RLEList_t));
    if(!list->next){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    list = list->next;  //is this hoe i should add the value? first to make new node and then put the char in the new one?
    list->data = value;
    assert(list->next);
    return RLE_LIST_SUCCESS;
}

/**
* RLEListSize: Returns the total number of characters in an RLE list.
* @param list - The RLE list whose size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the total number of characters in the list.
*/
int RLEListSize(RLEList list)
{
    int count = 0;
    if(list == NULL){
        return -1;
    }
    RLEList temp = list;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    return count;
}