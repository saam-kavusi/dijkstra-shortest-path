// Saam Kavusi
// 1229746585

#ifndef PJ3_HEAP_H
#define PJ3_HEAP_H

#include "data_structures.h"

// Min-heap API on VERTEX* (ordered by vertex->key).
// Implementations should maintain VERTEX::position on swaps.

HEAP*   create_heap(int capacity);     // allocate heap with given capacity
void    destroy_heap(HEAP* hp);        // free heap internals and heap itself
void    heap_reset(HEAP* hp);          // set size to 0
void    heap_insert(HEAP* hp, VERTEX* x);                 // insert pointer; bubble-up
VERTEX* heap_extract_min(HEAP* hp);                       // remove and return min
void    heap_decrease_key(HEAP* hp, int pos, double newkey); // decrease and bubble-up
bool    heap_empty(const HEAP* hp);    // true iff size == 0

#endif //PJ3_HEAP_H