#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* inStream){
    assert(inStream);
    if (inStream == NULL){
        return NULL;
    }
    RLEList list = RLEListCreate();
    char currentCharecter = 0;
    while((currentCharecter = (char)fgetc(inStream)) != EOF){
        RLEListResult appendResult = RLEListAppend(list, currentCharecter);
        if(appendResult != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            return NULL;
        }
    }
    return list;
}


RLEListResult asciiArtPrint(RLEList list, FILE* outStream){
    assert(outStream);
    assert(list);
    if(list == NULL || outStream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int listSize = RLEListSize(list);
    RLEListResult rleResult;
    for(int i=0; i<listSize; i++){
        if(fputc(RLEListGet(list, i, &rleResult), outStream) == EOF){
            return rleResult;
        }
    }
    return RLE_LIST_SUCCESS; 
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* outStream){
    assert(outStream);
    if(list == NULL || outStream == NULL){
        printf("Null arguement");
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult rleResult;
    char* encodedStr = RLEListExportToString(list, &rleResult);
    if(rleResult == RLE_LIST_SUCCESS){
        if(fputs(encodedStr, outStream) == EOF){
            free(encodedStr);
            return RLE_LIST_ERROR;
        }else{
            free(encodedStr);
            return RLE_LIST_SUCCESS;
        }
    }else{
        free(encodedStr);
        return rleResult;
    }
}
