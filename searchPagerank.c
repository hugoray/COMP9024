//
// Created by HUGO on 28/1/20.
//

#include "DLListStr.h"
#include "readdata.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_STRING 1000

void searchInvertedDLList(DLListStr paramsList, DLListStr pageRankList, DLListStr invertedIndexList,
                          DLListStr searchResultList) {
    // check all DDL is NULL or Not
    assert(paramsList != NULL);
    assert(pageRankList != NULL);
    assert(invertedIndexList != NULL);
    assert(searchResultList != NULL);

    searchpgrnk(paramsList, pageRankList, invertedIndexList, searchResultList);

}
int main(int argc, char *argv[]) {
    // check params have passed
    assert(argc > 1);

    // init
    DLListStr paramsList = newDLListStr();
    DLListStr pageRankList = newDLListStr();
    DLListStr invertedList = newDLListStr();
    DLListStr searchPagerank = newDLListStr();

    int var = 1;
    while (var < argc) {
        insertSetOrd(paramsList, argv[var]);
        var ++;
    }

    readPagerank(pageRankList);
    //showDLListStr(pageRankList);
    readInverted(invertedList);
    //showDLListStr(invertedList);

    searchInvertedDLList(paramsList,pageRankList,invertedList,searchPagerank);

    showDLListStr(searchPagerank);
    // release all the list
    freeDLListStr(paramsList);
    freeDLListStr(invertedList);
    freeDLListStr(pageRankList);
}