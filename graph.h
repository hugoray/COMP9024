//
// Created by HUGO on 23/1/20.
// based on https://webcms3.cse.unsw.edu.au/COMP9024/20T0/resources/39779
//

#include <stdbool.h>

#ifndef COMP9024_GRAPH_H
#define COMP9024_GRAPH_H

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);

int getNumberOfOutDegrees(Graph,Vertex);

#endif //COMP9024_GRAPH_H
