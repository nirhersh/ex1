#include "AsciiArtTool.h"
#include <string.h>

#define INVERTED "-i"
#define ENCODED "-e"
#define INVERT_ONE '@'
#define INVERT_TWO ' '
#define EQUAL 0

static char invertMapFunction(char c);

int main(int argc, char** argv){
    if(argc != 4){
        printf("Usage: ./AsciiArtTool <flag><source><target>\n");
        return 0;
    }

    FILE* source = fopen(argv[2], "r");
    if(!source)
    {
        printf("%s not found\n", argv[2]);
        return 0;
    }
    FILE* target = fopen(argv[3], "w");
    RLEList list = asciiArtRead(source);
    assert(list);

    if(strcmp(argv[1], INVERTED) == EQUAL){
       if (RLEListMap(list, invertMapFunction) != RLE_LIST_SUCCESS){
           printf("Error inverting ascii picture\n");
       }else{
           if(asciiArtPrint(list, target) != RLE_LIST_SUCCESS){
               printf("Error printing inverted ascii picture\n");
           }
       }
    }else if(strcmp(argv[1], ENCODED) == EQUAL){
        RLEListResult result = 0;
        result = asciiArtPrintEncoded(list, target);
        if(result != RLE_LIST_SUCCESS){
            printf("Error printing encoded format to the target file\n");
        }
    }else{
        printf("Unrecognised flag. Use -i for inverted or -e for encoded\n");
    }
    
    RLEListDestroy(list);
    fclose(source);
    fclose(target);
    return 0;
}

static char invertMapFunction(char c){
    if (c == INVERT_ONE){
        return INVERT_TWO;
    }else if(c == INVERT_TWO){
        return INVERT_ONE;
    }else{
        return c;
    }
}
