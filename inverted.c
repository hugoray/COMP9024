//
// Created by HUGO on 25/1/20.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "DLListStr.h"
#include "readdata.h"
#include <stdlib.h>

#define MAX_STRING 1000

int main() {
    // read from collection.txt
    DLListStr collectionUrl = newDLListStr();
    readCollection(collectionUrl);
    sortDLLBySelectionurl(collectionUrl);
    //showDLListStr(collectionUrl);
    //printf("%d",strcmp("url11","url33"));

    // get the length of list
    int numberofurl = lengthDLListStr(collectionUrl);

    //convert list to array
    char **urlarray = malloc(numberofurl * sizeof(char *));
    convertDLLtoArray(collectionUrl, urlarray);

    DLListStr invertedList = newDLListStr();
    readSection2(urlarray, invertedList, numberofurl);

    // debug: print list
    //showDLListStr(invertedList);

    // sort list
    sortDLLBySelection(invertedList);

    // debug: print list
    //printf("******************Inverted List*******************\n");
    //showDLListStr(invertedList);

    // output the text file
    display(invertedList);

    // free
    freeDLListStr(collectionUrl);
    freeDLListStr(invertedList);

    for (int i = 0; i < numberofurl; i++) {
        free(urlarray[i]);
    }
    free(urlarray);
}