#include "AsciiArt.h"

RLEList asciiArtRead(FILE* in_stream){
    assert(in_stream);
    if (in_stream == NULL){
        return NULL;
    }
    RLEList list = RLEListCreate();
    char current_charecter = 0;
    while((current_charecter = (char)fgetc(in_stream))){
        RLEListResult append_result = RLEListAppend(list, current_charecter);
        if(append_result != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            return NULL;
        }
    }
    return list;
}


RLEListResult asciiArtPrint(RLEList list, FILE* out_stream){
    assert(out_stream);
    assert(list);
    if(list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int list_size = RLEListSize(list);
    RLEListResult rle_result;
    for(int i=0; i<list_size; i++){
        if(fputc(RLEListGet(list, i, &rle_result), out_stream) == EOF){
            return rle_result;
        }
    }
    return RLE_LIST_SUCCESS; 
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream){
    assert(out_stream);
    if(list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult rle_result;
    char* encoded_str = RLEListExportToString(list, &rle_result);
    if(rle_result == RLE_LIST_SUCCESS){
        if(fputs(encoded_str, out_stream) == EOF){
            free(encoded_str);
            return RLE_LIST_ERROR;
        }else{
            free(encoded_str);
            return RLE_LIST_SUCCESS;
        }
    }else{
        free(encoded_str);
        return rle_result;
    }
}
