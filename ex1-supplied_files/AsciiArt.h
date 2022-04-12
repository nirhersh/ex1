//
// Created by Nir on 10/4/2022
//

#ifndef HW1_ASCIIART_H
#define HW1_ASCIIART_H
#define NEWLINE '\n'

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "RLEList.h"

/**
 * Ascii Art Read and Write
 * 
 * Implementing a program for compressing, reading and writing Ascii art pictures.
 * 
 * The following functions are available:
 *   asciiArtRead            - Reads a file and compresses it using RLE
 *   asciiArtPrint           - Writes an ascii picture using RLEList to a file
 *   asciiArtPrintEncoded    - Writes an ascii picture to a file in a compressed format  
 */


/**
*   asciiArtRead: reads a given file and compress it using RLE.
*   Note that the user must free the returned list using RLEListDestroy() once it is no longer needed.
*
* @param in_stream - The input stream of the file containing the ascii picture.
* @return
* 	A new RLEList.
*   In the case of a failure in reading the charecter from the file returns NULL.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
*   asciiArtPrint: writes a picture that is represented as an RLEList into a file.
*
* @param list - An RLEList that contains the charecters for the picture.
* @param out_stream - The stream to the file that the function write to.
* @return
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the ascii picture was written successfully to the file.
*/
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);


/**
*   asciiArtPrintEncoded: writes an ascii picture in an encoded format to a file.
*
* @param list - An RLEList that contains the charecters for the picture.
* @param out_stream - The stream to the file that the function write to.
* @return
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the ascii picture was written in an encoded format successfully to the file.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);


#endif // HW1_ASCIIART_H
