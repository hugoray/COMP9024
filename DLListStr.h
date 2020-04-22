// DLListStr.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2020 

#ifndef DLListStr_H
#define DLListStr_H

#include <stdio.h>
#include "DLListStr.h"

// External view of DLListStr
// Implementation given in DLListStr.c
// Implements a DLListStr of string 

typedef struct DLListRep *DLListStr;

// create a new empty DLListStr
DLListStr newDLListStr();

// insert value by order
void insertSetOrd(DLListStr L, char *);

// free up all space associated with list
void freeDLListStr(DLListStr);

// display items from a DLListStr, comma separated
void showDLListStr(DLListStr);

// display to the file
void display(DLListStr);

// get the length of DLL
int lengthDLListStr(DLListStr);

// convert DLL to array
void convertDLLtoArray(DLListStr, char **);

// insert value and child
void insertChild(DLListStr , char *, char *);

// sort DLL by using selection algorithm
void sortDLLBySelection (DLListStr);

// sort collectionurl for part 2
void sortDLLBySelectionurl(DLListStr);

// for searchpagerank part
void insertDLListPageRank(DLListStr , char *, double);

// for searchpagerank part
void sortDLLBySelection2(DLListStr);

// for searchpagerank part
void searchpgrnk(DLListStr, DLListStr, DLListStr, DLListStr);

#endif
