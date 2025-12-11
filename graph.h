// Saam Kavusi
// 1229746585

#ifndef PJ3_GRAPH_H
#define PJ3_GRAPH_H

#include "data_structures.h"

struct GRAPH;

// Loads graph from file; builds internal structures according to GraphType × Flag.
GRAPH* load_graph(const char* filename, const char* graphType, int flag);

// Frees all dynamic allocations associated with the graph.
void    destroy_graph(GRAPH* G);

// Prints adjacency lists with required formatting.
void    print_adj(const GRAPH* G);

// Runs Dijkstra single-pair with early stop.
void    shortest_path_single_pair(GRAPH* G, int start, int terminate, HEAP* heap);

// Runs Dijkstra single-source (no early stop).
void    shortest_path_single_source(GRAPH* G, int start, HEAP* heap);

// Prints the shortest path if valid; otherwise prints required "no path" line.
void    print_path(GRAPH* G, int start, int terminate, STACK* st);

// Prints the length if valid; otherwise prints required "no path" line.
void    print_length(GRAPH* G, int start, int terminate);

#endif //PJ3_GRAPH_H