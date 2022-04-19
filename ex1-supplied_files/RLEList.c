#include "RLEList.h"  
#include <assert.h>
#include <stdlib.h>

#define NEWLINE '\n'
#define NULL_CHAR '\0'

struct RLEList_t{
    char data;
    int repetitions;
    RLEList next;
};

static int exportStringSize(RLEList list);
static int numOfDigits(int num);
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
    list->data = NULL_CHAR;
    list->repetitions = 0;
    list->next = NULL;
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
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList temp = list;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    if(temp->repetitions == 0){
        temp->data= value;
        temp->repetitions++;
        //printf("appended %c it has %d repetitons\n", temp->data, temp->repetitions);
        return RLE_LIST_SUCCESS;
    }
    if(temp->data == value){
        temp->repetitions++;
      //  printf("appended %c it has %d repetitons\n", temp->data, temp->repetitions);
        return RLE_LIST_SUCCESS;
    }
    temp->next = malloc(sizeof(*temp));
    assert(temp->next != NULL);
    if(temp->next == NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    temp = temp->next;
    temp->data = value;
    temp->repetitions = 1;
    temp->next = NULL;
    //printf("appended %c it has %d repetitons\n", temp->data, temp->repetitions);
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
    int counter = 0;
    if(list == NULL){
        return -1;
    }
    RLEList temp = list;
    while (temp)
    {
        counter += temp->repetitions;
        temp = temp->next;
    }
    return counter;
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
    //printf("temp next next char is%c\n", list->next->next->data);
    assert(list);
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList temp = list;
    RLEList previous = list;
    int tempSize =  RLEListSize(temp);
    assert(index < tempSize);
    if(index > tempSize){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int counter = 0;
    while(counter + (temp->repetitions) <= index)
    {
        counter += temp->repetitions;
        previous = temp;
        temp = temp->next;
        assert(temp != NULL);
    }
    // now we are sure that temp points on the node with the char to be removed
    if(temp->repetitions > 1){
        temp->repetitions--;
        return RLE_LIST_SUCCESS;
    }
    if(index == 0){ //if case this is the first node and need to be removed:
        
        temp->data = temp->next->data;
        temp->repetitions = temp->next->repetitions;
        RLEList toDelete = temp->next;
        temp->next = (temp->next)->next;
        free(toDelete);
        return RLE_LIST_SUCCESS;
    }
    // in case we need to delete temp: (prev points on the node before temp and 
    //    prev.next will be reset as the one after temp)
    //check if the next node consist the same char and if it is, merges the nodes:
    if((temp->next) && (previous->data == temp->next->data)){
        previous->repetitions += temp->next->repetitions;
        previous->next = temp->next->next;
        free(temp->next); //after merge, free the second 
    }
    else{
        previous->next = temp->next;
    }
    free(temp);
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
    //printf("%c, ", list->data);
    RLEList temp = list;
    if(temp == NULL){
        if(result != NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(index > RLEListSize(temp)){
        if(result != NULL){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
        }
    }
    int counter = 0;
    while(counter + temp->repetitions <= index)
    {
        counter += temp->repetitions;
        temp = temp->next;
        assert(temp != NULL);
    }
    
    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
        }
    return temp->data;

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
    RLEList temp = list; 
    int size = exportStringSize(temp); //length of the string
    char* string = (char*)malloc(size*sizeof(char)); //nultiply by 3 to make place for the char, the repetitions and the \n
    assert(string != NULL);
    if(string == NULL)
    {
        *result = RLE_LIST_ERROR;
        return NULL;
    }
    char* stringPtr = string;
    while (temp != NULL)
    {
        (*string) = temp->data;
        ++string;
        int offset = 0;
        // return null in case of failure
        if((offset = sprintf(string, "%d", temp->repetitions)) < 0){
            *result = RLE_LIST_ERROR;
            return NULL;
        }
        string += offset;
        (*string) = NEWLINE;
        temp = temp->next;
        string++;
    }
    (*string) = NULL_CHAR;
    *result = RLE_LIST_SUCCESS;
    return stringPtr;
}

static int exportStringSize(RLEList list)
{
    int counter = 0;
    RLEList temp = list;
    while (temp != NULL)
    {
        int length = numOfDigits(temp->repetitions);
        counter+=(length+1);
        counter++; //for the \n or \0
        temp = temp->next;
    }
    return counter;
}

static int numOfDigits(int num)
{
    int count = 0;
    while(num > 0)
    {
        count ++;
        num = num / 10;
    }
    return count;
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
    RLEList temp = list;
    char replace;
    while(temp != NULL)
    {
        replace = map_function(temp->data); /////////////////////is this the way i should use function pointer?
        temp->data = replace;
        temp = temp->next;
    }
    return RLE_LIST_SUCCESS;
}