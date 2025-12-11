// Saam Kavusi
// 1229746585

#include <cstdio>
#include <stdlib.h>

#include "data_structures.h"
#include "heap.h"

/* Helper Function */

// family helpers
static int left_child(int i) {return 2 * i;}
static int right_child(int i) {return 2 * i + 1;}
static int parent(int i) {return i / 2;}

// switching nodes: [i] -> [j] to [j] -> [i] & update position
static void node_switch(HEAP* hp, int i, int j)
{
    // put the nodes into pointers to the vertices
    pVERTEX vi = hp -> H[i];
    pVERTEX vj = hp -> H[j];

    // put values from pointer [j] into H[i] & update position
    hp -> H[i] = vj;
    vj -> position = i;

    // put values from [i] into H[j] & update positions
    hp -> H[j] = vi;
    vi -> position = j;
}

// determines if vertex a has smaller key/index (index - coming before b)
static int smaller_vertex(pVERTEX a, pVERTEX b)
{
    if (a -> key < b -> key) return 1; // a.key < b.key
    if (a -> key > b -> key) return 0; // a.key > b.key
    //if keys are ==, returns smaller index (1 if a comes first 0 if b)
    return (a -> index < b -> index);
}

// does bubbling up
static void bubble_up(HEAP *hp, int i)
{
    int parentIndex; // holds parent index
    while (i > 1)    // bubbles up till root
    {
        parentIndex = parent(i); // parent index for current position
        // if parent key <= child key we stop
        if (!smaller_vertex(hp -> H[i], hp -> H[parentIndex])) {break;}
        // if parent key > child key we switch child and parent
        node_switch(hp, i, parentIndex);
        i = parentIndex; // move index up
    }
}

// heapify top down
static void heapify_down(HEAP *hp, int i)
{
    int n;        // store heap size
    int left;     // stores left child
    int right;    // stores right child
    int smallest; // stores smallest

    n = hp -> size;

    for (;;) // infinite loop till break point
    {
        left = left_child(i);
        right = right_child(i);
        smallest = i;

        // assign smallest as left
        if (left <= n && smaller_vertex(hp -> H[left], hp -> H[smallest])) {smallest = left;}

        // assign smallest as right
        if (right <= n && smaller_vertex(hp -> H[right], hp -> H[smallest])) {smallest = right;}

        // we have smallest so exit loop
        if (smallest == i) {break;}

        // switch nodes around
        node_switch(hp, i, smallest);

        // assigns new smallest
        i = smallest;
    }

}

/* Heap Functions */

HEAP* create_heap(int capacity)
{
    if (capacity < 1) return NULL; //if capacity <= 0 return
    HEAP* hp = (HEAP*)calloc(1, sizeof(HEAP)); // allocate mem for heap struct
    if (!hp) return NULL; // make sure allocation worked

    // initialize capacity and size
    hp -> capacity = capacity;
    hp -> size = 0;
    // allocate mem for the array that holds vertex pointers (1 based index)
    hp -> H = (pVERTEX*)calloc(capacity + 1, sizeof(pVERTEX));
    if (!hp -> H) // check if allocation worked, if not free
    {
        free(hp); // free heap struct
        return NULL;
    }
    return hp; // return pointer pointing to heap
}

void destroy_heap(HEAP* hp)
{
    if (!hp) return; // if no heap return
    if (hp -> H) free(hp -> H); // free array of vertex pointers
    free(hp); // free heap struct
}

void heap_reset(HEAP* hp)
{
    int i; // counter

    if (!hp) return; // check if empty heap
    for (i = 1; i <= hp -> size; i++) // go through heap
    {
        if (hp -> H[i]) hp -> H[i] -> position = 0; // resets positions to 0
        hp -> H[i] = NULL; // heap points to NULL
    }
    hp -> size = 0; // rest size to 0
}

void heap_insert(HEAP* hp, VERTEX* x)
{
    int newIndex;          // holds increased size value

    // checks
    if (!hp || !x) return; // if NULL = heap pointer or vertex pointer exit
    if (hp -> size == hp -> capacity) {return;} // if heap is full return
    // insert
    (hp -> size)++;           // increase size
    newIndex = hp -> size;    // update index
    hp -> H[newIndex] = x;    // put new vertex/node at end of heap
    x -> position = newIndex; // update position in vertex
    bubble_up(hp, newIndex);  // keep heap properties
}

VERTEX* heap_extract_min(HEAP* hp)
{
    if (!hp || hp -> size == 0) return NULL; //check if doesnt exist or empty

    pVERTEX vertexMin = hp -> H[1];    // grabs index
    hp -> H[1] = hp -> H[hp -> size];  // puts last element into root position

    if (hp -> H[1]) {hp -> H[1] -> position = 1;} // update position of the new root
    hp -> H[hp -> size] = NULL; // clear last heap slot
    hp -> size--; // reduce heap size

    if (hp -> size >= 1) heapify_down(hp, 1); // preserve heap property
    if (vertexMin) vertexMin -> position = 0;   // remove extracted root from heap

    return vertexMin; // return the original root / the smallest value
}

void heap_decrease_key(HEAP* hp, int pos, double newkey)
{
    if (!hp || pos < 1 || pos > hp -> size) return; // checks
    pVERTEX vertex = hp -> H[pos];
    if (!vertex) return; // check allocation
    if (newkey >= vertex -> key) return; // check newKey against current key
    // decrease key
    vertex -> key = newkey;
    bubble_up(hp, pos);
}

bool heap_empty(const HEAP* hp)
{
    return (!hp || hp -> size == 0); // if heap doesnt exist or size is 0 return true
}
