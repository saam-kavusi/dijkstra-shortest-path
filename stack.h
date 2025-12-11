// Saam Kavusi
// 1229746585

#ifndef PJ3_STACK_H
#define PJ3_STACK_H

#include "data_structures.h"

// Simple stack for vertex indices (or VERTEX*).
STACK* create_stack(int capacity); // allocate stack with capacity
void   destroy_stack(STACK* st);   // free stack
void   stack_clear(STACK* st);     // top ← -1
void   push(STACK* st, int v);     // push value
int    pop(STACK* st);             // pop value
bool   empty(const STACK* st);     // true iff empty

#endif //PJ3_STACK_H