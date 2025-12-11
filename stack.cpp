// Saam Kavusi
// 1229746585

#include <stdlib.h>

#include "data_structures.h"
#include "stack.h"

// allocate stack with capacity
STACK* create_stack(int capacity)
{
    if (capacity < 1) return nullptr; // capacity has to be 1 or more

    STACK *st = (STACK*) calloc(1,sizeof(STACK)); // allocate mem for stack struct
    if (!st) return nullptr; // make sure allocation succeeded

    // allocate memory for int array storing vertex index
    st -> vIndex = (int*) malloc( sizeof(int) * capacity);
    if (!st -> vIndex) // if allocation failed
    {
        free(st); // free up stack struct
        return nullptr;
    }

    // initialize stack
    st->capacity = capacity;
    st->top = -1; // -1 means empty stack
    return st; // returning pointer pointing to the new stack in the heap
}

// free stack
void destroy_stack(STACK* st)
{
    if (!st) return; // if stack pointer is NLL
    if (st -> vIndex) free(st -> vIndex); // free memory of int array of indices
    free(st); // free memory for pointer
}

// top ← -1
void stack_clear(STACK* st)
{
    if (!st) return; // return if stack pointer is NULL
    st -> top = -1; // top of stack is -1 meaning empty stack
}

// push value
void push(STACK* st, int v)
{
    if (!st) return; // if stack pointer is pointing to NULL return
    // if adding another element would be more than capacity, return
    if (st -> top + 1 >= st->capacity) return;
    // else push
    st -> vIndex[++(st -> top)] = v;
}

// pop value
int pop(STACK* st)
{
    if (!st || st -> top < 0) return -1; // if pointing to NULL or if empty
    return st -> vIndex[(st -> top)--]; // else pop
}

// true iff empty
bool empty(const STACK* st)
{
    return(!st || st -> top < 0); // returns true if empty or pointing to null
}
