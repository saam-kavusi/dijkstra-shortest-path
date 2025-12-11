// Saam Kavusi
// 1229746585

#include <stdio.h>
#include <stdlib.h>

#include "data_structures.h"
#include "util.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "main.h"

int main(int argc, char** argv)
{
   if (!validate_cli_or_exit(argc, argv)) //validates command line
   {
       return 0; //if incorrect command line stops program
   }

   // parse arguments
   const char *inputFile = argv[1];
   const char *graphType = argv[2];
   const int  flag       = atoi(argv[3]); // parse: 0 = insert front| 1= insert rear

   // builds graphs
   GRAPH* G = load_graph(inputFile, graphType, flag);
   if (!G)
   {
        fprintf(stderr, "Input file is invalid.\n");
        return 0;
   }

   // Create heap/stack with capacity = (n) number of vertices (to be known from G).
   HEAP*  heap  = create_heap(G -> n);
   STACK* st = create_stack(G -> n);

   if (!heap || !st) // if couldnt be made exit
   {
        if (heap) destroy_heap(heap);
        if (st) destroy_stack(st);
        destroy_graph(G);
        return 0;
   }

   // Run instruction loop (reads stdin, writes stdout/stderr).
   instruction_loop(G, heap, st);

   // Cleanup.
   destroy_stack(st);
   destroy_heap(heap);
   destroy_graph(G);
   return 0;
}