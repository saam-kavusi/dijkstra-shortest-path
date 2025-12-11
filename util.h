// Saam Kavusi
// 1229746585

#ifndef PJ3_UTIL_H
#define PJ3_UTIL_H

#include "data_structures.h"
#include "graph.h"

// Validates CLI; on invalid, prints exact Usage to stderr and returns false.
bool validate_cli_or_exit(int argc, char** argv);

// Runs the instruction loop reading stdin and dispatching to GRAPH ops.
void instruction_loop(GRAPH* G, HEAP* heap, STACK* st);

#endif //PJ3_UTIL_H