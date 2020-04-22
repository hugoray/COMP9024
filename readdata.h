//
// Created by HUGO on 22/1/20.
//

#ifndef COMP9024_20T0_PUBLIC_READDATA_H
#define COMP9024_20T0_PUBLIC_READDATA_H

#include <string.h>
#include <stdio.h>

#define MAX_STRING 1000

// read file from collection to DLL
void readCollection(DLListStr);

// read section 1 to the graph
void readSection1(char **, Graph, int);

// read section 2 to the graph
void readSection2(char **, DLListStr, int);

// read pagerank.txt
void readPagerank(DLListStr);

// read inverted.txt
void readInverted(DLListStr);

#endif //COMP9024_20T0_PUBLIC_READDATA_H
