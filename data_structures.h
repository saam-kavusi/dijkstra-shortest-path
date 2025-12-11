// Saam Kavusi
// 1229746585

#ifndef PJ3_DATA_STRUCTURES_H
#define PJ3_DATA_STRUCTURES_H

typedef enum
{
    WHITE = 0,
    GRAY  = 1,
    BLACK = 2
} COLOR;

typedef struct TAG_VERTEX
{
    int    index;    // vertex ID
    COLOR  color;    // Dijkstra State
    double key;      // current best distance from source
    int    pi;       // parent
    int    position; // index within heap array
} VERTEX;

typedef VERTEX  *pVERTEX;      //  pointer for vertices

typedef struct TAG_NODE
{
    int index;      // index of edge
    int u;          // vertex 1 of edge
    int v;          // vertex 2 of edge
    double w;       // weight
    TAG_NODE *next; // points to the next edge
} NODE;

typedef NODE *pNODE; // pointer to nodes

typedef struct TAG_HEAP
{
    int capacity; // capacity of the heap/max number of items
    int size;     // current size of the heap
    pVERTEX *H;   // pointer for vertices inside heap
}HEAP;

typedef HEAP *pHEAP;   // pointer for the heap

typedef struct TAG_STACK
{
    int capacity;  // max slots
    int top;       // index of top element (-1 when empty)
    int *vIndex; // stores vertex indices
} STACK;

typedef STACK *pSTACK; // pointer to a stack

struct GRAPH
{
    int n;         // vertices
    int m;         // edges
    pVERTEX *V;    // pointer to vertex
    pNODE   *Adj;  // head of adj list

    enum
    {
        NONE          = 0,
        SINGLE_PAIR   = 1,
        SINGLE_SOURCE = 2
    } last_mode;

    int last_source;
    int last_destination; // -1 for single source
};

typedef GRAPH *pGRAPH; // graph pointer

#endif //PJ3_DATA_STRUCTURES_H