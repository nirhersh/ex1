#include "test_utilities.h"
#include "../AsciiArtTool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWLINE '\n'

bool test1(FILE* in_stream);
bool test2(FILE* in_stream, FILE* out_stream);
bool test3(FILE* in_stream, FILE* out_stream, FILE* encoded_stream);
static bool compareFiles(FILE* stream1, FILE* stream2);

int main(int argc, char **argv){
    // must get file input and file output to perform the tests
    if(argc < 2 || argc > 5){
        printf("Usage: test <file_input> <file_output> <expected_encoded_file>\n");
        return 0;
    }
    FILE* in_stream = fopen(argv[1], "r");
    FILE* out_stream = NULL;
    FILE* encoded_stream = NULL; 
    // open output stream if given
    if (argc >= 3){
        out_stream = fopen(argv[2], "w+");
    }

    if (argc == 4){
        encoded_stream = fopen(argv[3], "r");
    }

    // run first test
    printf("----------------Starting tests----------------\n");
    bool test1_result = test1(in_stream);
    bool test2_result = true, test3_result = true;

    //run other tests if the file is given
    if(out_stream != NULL){
        fseek(in_stream, 0, SEEK_SET);
        test2_result = test2(in_stream, out_stream);
        fclose(out_stream);
    }else{
        printf("For the next tests give an output file\n");
    }

    if(encoded_stream != NULL){
        fseek(in_stream, 0, SEEK_SET);
        out_stream = fopen(argv[2], "w+");
        test3_result = test3(in_stream, out_stream, encoded_stream);
        fclose(encoded_stream);
        fclose(out_stream);
    }

    if(test1_result && test2_result && test3_result){
        printf("Tests passed\n");
    }else{
        printf("Failed tests\n");
    }

    fclose(in_stream);
    return 0;

}


bool test1(FILE* in_stream){
    printf("\n----------------Starting test 1----------------\n");
    RLEList list = asciiArtRead(in_stream);
    assert(list);
    RLEListResult result;
    fseek(in_stream, 0, SEEK_SET);
    for(int i=0; i<RLEListSize(list); i++){
        char rle_list_char = RLEListGet(list, i, &result);
        if(result != RLE_LIST_SUCCESS){
            printf("Failed getting the char from the list at index %d, got error code %d", i, result);
            RLEListDestroy(list);
            return false;
        }
        char file_char = (char)fgetc(in_stream);
        if(rle_list_char != file_char){
            printf("Chars are different %c != %c", rle_list_char, file_char);
            RLEListDestroy(list);
            return false;
        }
    }
    printf("file was read successfully\nEnd of test1\n\n");
    RLEListDestroy(list);
    return true;
}

bool test2(FILE* in_stream, FILE* out_stream){
    printf("----------------Starting test 2----------------\n");
    RLEList list = asciiArtRead(in_stream);
    assert(list);
    RLEListResult result;
    fseek(in_stream, 0, SEEK_SET);
    result = asciiArtPrint(list, out_stream);
    assert(result == RLE_LIST_SUCCESS);
    bool is_file_identical = compareFiles(in_stream, out_stream);
    RLEListDestroy(list);
    if(is_file_identical){
        printf("file was printed successfully\nEnd of test2\n\n");
        return true;
    }else{
        printf("files was not printed successfully, input and output files are different\nEnd of test2\n\n");
        return false;
    }
}


bool test3(FILE* in_stream, FILE* out_stream, FILE* encoded_stream){
    printf("----------------Starting test 3----------------\n");
    RLEList list = asciiArtRead(in_stream);
    assert(list);
    RLEListResult result;
    fseek(in_stream, 0, SEEK_SET);
    result = asciiArtPrintEncoded(list, out_stream);
    fseek(out_stream, 0, SEEK_SET);
    assert(result == RLE_LIST_SUCCESS);
    bool is_file_identical = compareFiles(encoded_stream, out_stream);
    RLEListDestroy(list);
    if(is_file_identical){
        printf("file was printed successfully\nEnd of test3\n\n");
        return true;
    }else{
        printf("files was not printed successfully, expected output and output files are different\nEnd of test3\n\n");
        return false;
    }
}

static bool compareFiles(FILE* stream1, FILE* stream2){
    char c1 = fgetc(stream1), c2 = fgetc(stream2);
    while(c1 != EOF && c2 != EOF){
        if(c1 != c2){
            printf("Two chars are different: %c %c", c1, c2);
            return false;
        }
        c1 = fgetc(stream1);
        c2 = fgetc(stream2);
    }
    return true;
}
