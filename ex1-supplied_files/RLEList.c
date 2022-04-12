#include "RLEList.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

//this function gets a pointer to a RLElist and returns the num of Nodes in the RLElist;
int RLECountNodes(RLEList list);
struct RLEList_t{
    char Data;
    int Repetitions;
    struct RLElist_t* next;
};

//implement the functions here

RLEList RLEListCreate()
{
    RLEList list = NULL;
    list = malloc(sizeof(*list)); 
    if(!list)
    {
        return NULL;
    }
    assert(list);
    list->Data = '\0';
    list->Repetitions = 0;
    list->next = NULL;
    return list;
}


void RLEListDestroy(RLEList list)
{
    while (list)
    {
        RLEList ToDelete = list;
        list = list->next;
        free(ToDelete);
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
    if (value == NULL || list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList Temp = list;
    while (Temp->next != NULL)
    {
        Temp = Temp->next;
    }
    if(Temp->Repetitions == 0){
        Temp->Data
 = value;
        Temp->Repetitions++;
        return RLE_LIST_SUCCESS;
    }
    if(Temp->Data == value){
        Temp->Repetitions++;
        return RLE_LIST_SUCCESS;
    }
    Temp->next = malloc(sizeof(*Temp));
    assert(Temp->next != NULL);
    if(Temp->next == NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    Temp = Temp->next;
    Temp->Data = value;
    Temp->Repetitions++;
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
    int Counter = 0;
    if(list == NULL){
        return -1;
    }
    RLEList Temp = list;
    while (Temp)
    {
        Counter += Temp->Repetitions;
        Temp = Temp->next;
    }
    return Counter;
}

/**
*   RLEListRemove: Removes a character found at a specified index in an RLE list.
*
* @param list - The RLE list to remove the character from.
* @param index - The index at which the character to be removed is found.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	RLE_LIST_SUCCESS the character found at index has been removed successfully.
*/
RLEListResult RLEListRemove(RLEList list, int index) ///////////////////assumed 0 is the index of the first node
{
    if(list == NULL || index == NULL)
    return RLE_LIST_NULL_ARGUMENT;
    RLEList Temp = list;
    RLEList Previous = list;
    if(index > RLEListSize(Temp));{
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int Counter = 0;
    while(Counter + Temp->Repetitions < index)
    {
        Counter += Temp->Repetitions;
        Previous = Temp;
        Temp = Temp->next;
        assert(Temp != NULL);
    }
    // now we are sure that temp points on the node with the char to be removed
    if(Temp->Repetitions > 1){
        Temp->Repetitions --;
        return RLE_LIST_SUCCESS;
    }
    // in case we need to delete temp: (prev points on the node before temp and 
    //    prev.next will be reset as the one after temp)
    Previous->next = Temp->next;
    free(Temp);
    return RLE_LIST_SUCCESS;


}

/**
*   RLEListGet: Returns the character found at a specified index in an RLE list.
*
* @param list - The RLE list to retrieve the character from.
* @param index - The index at which the character to be retrieved is found.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	LIST_SUCCESS the character found at index has been retrieved successfully.
* @return
* 	0 if result is not RLE_LIST_SUCCESS.
* 	The character found at given index in case of success.   
*/
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    RLEList Temp = list;
    if(Temp == NULL){
        if(result != NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(index > RLEListSize(Temp));{
        if(result != NULL){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
        }
    }
    int Counter = 0;
    while(Counter + Temp->Repetitions < index)
    {
        Counter += Temp->Repetitions;
        Temp = Temp->next;
        assert(Temp != NULL);
    }
    
    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
        }
    return Temp->Data;

}

/**
*   RLEListExportToString: Returns the characters found in an RLE list as a string.
*
* @param list - The RLE list to be exported as a string.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	LIST_SUCCESS the RLE list has been successfuly exported as a string.
* @return
* 	NULL if result is not RLE_LIST_SUCCESS.
* 	The string that corresponds to the received RLE list.
*/
char* RLEListExportToString(RLEList list, RLEListResult* result) //////////should i malloc the string for the chars?
{
    if(list == NULL){
        if(result != NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    RLEList Temp = list; 
    int Size = RLECountNodes(Temp);
    char* String = (char*)malloc(Size*sizeof(char)*3); //nultiply by 3 to make place for the char, the repetitions and the \n
    assert(String != NULL);
    if(String == NULL)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    char* StringPtr = String;
    while (Temp != NULL)
    {
        StringPtr[0] = Temp->Data;
        StringPtr[1] = (char)Temp->Repetitions;
        StringPtr[2] = '\n';
        Temp = Temp->next;
        StringPtr += 3;
    }

}

int RLECountNodes(RLEList list)
{
    int Counter = 0;
    RLEList Temp = list;
    while (Temp != NULL)
    {
        Counter++;
        Temp = Temp->next;
    }
    return Counter;
}

/**
*   RLEListMap: Change the given RLE list's characters according to the received mapping function.
*               This function replaces each character of the give RLE list with its mapped character.
*
* @param list - The RLE list to edit.
* @param MapFunction - Pointer to a function of type MapFunction. 
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
* 	LIST_SUCCESS if the mapping is done successfully.
*/
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list == NULL || map_function == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    assert(list != NULL && map_function != NULL);
    RLEList Temp = list;
    char replace;
    while(Temp != NULL)
    {
        replace = map_function(Temp->Data); /////////////////////is this the way i should use function pointer?
        Temp->Data = replace;
        Temp = Temp->next;
    }
    return RLE_LIST_SUCCESS;
}