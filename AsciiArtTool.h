//
// Created by Adi on 23/04/2022.
//

#ifndef AsciiArtTool_H
#define AsciiArtTool_H

#include <stdio.h>
#include <stdbool.h>

// בר צריך להבין מה הן כלל הספריות שצריך להוסיף לפה^ אלה כבר היו פה סביר שצריך למחוק

/**
*   asciiArtRead: Reads the given file and uses RLE method to compress it.
*
* @param in_stream - An object of type FILE* that contains the picture to compress.
* @return
*     list of type RLEList that contains all characters in picture.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
*   asciiArtPrint: Writes a picture represented with a list of type RLEList into a file.
*
* @param list - The RLE list that contains all the characters in the picture.
* @param out_stream - An object of type FILE* to which we write the picture.
* @return
*     LIST_ERROR_RLE if an error has occured
*     Bar ani lo batuach shaze amoor lihiyot kacha rak omer
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
*   asciiArtPrintEncoded: Writes a given picture into a file in the compressed way.
*
* @param list - The RLE list that contains the characters in the picture.
* @param out_stream - An object of type FILE* to which we write the compressed picture.
* @return
*     RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL
*     RLE_LIST_SUCCESS in case of success
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // AsciiArtTool_H
