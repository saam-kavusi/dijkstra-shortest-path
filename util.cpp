// Saam Kavusi
// 1229746585

#include <cstdio>
#include <cstring>

#include "data_structures.h"
#include "graph.h"
#include "util.h"



// Validates CLI; on invalid, prints exact Usage to stderr and returns false.
bool validate_cli_or_exit(int argc, char** argv)
{
    const char *graphType;
    const char *flag;

    if (argc != 4) // checks command line
    {
        fprintf(stderr, "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n");
        return false;
    }

    graphType = argv[2]; // check graph type
    if (!(graphType && (strcmp(graphType, "DirectedGraph") == 0 || strcmp(graphType, "UndirectedGraph") == 0)))
    {
        fprintf(stderr, "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n");
        return false;
    }

    flag = argv[3]; // check flag
    if (!(flag && (strcmp(flag, "0") == 0 || strcmp(flag, "1") == 0)))
    {
        fprintf(stderr, "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n");
        return false;
    }

    return true; // everything good
}

// Runs the instruction loop reading stdin and dispatching to GRAPH ops.
void instruction_loop(GRAPH* G, HEAP* heap, STACK* st)
{
    char word[64];

    int  start;     // start of edge
    int  terminate; // end of edge

    while (scanf("%63s", word) == 1)
    {
        //Stop
        if (strcmp(word, "Stop") == 0) {break;}
        //PrintAdj
        if (strcmp(word, "PrintADJ") == 0) {print_adj(G);}
        //SinglePair
        else if (strcmp(word, "SinglePair") == 0)
        {
            if (scanf("%d %d", &start, &terminate) != 2)
            {
                fprintf(stderr, "Invalid instruction.\n");
                continue;
            }
            shortest_path_single_pair(G, start, terminate, heap);
        }
        //SingleSource
        else if (strcmp(word, "SingleSource") == 0)
        {
            if (scanf("%d", &start) != 1)
            {
                fprintf(stderr, "Invalid instruction.\n");
                continue;
            }
            shortest_path_single_source(G, start, heap);
        }
        //PrintLength
        else if (strcmp(word, "PrintLength") == 0)
        {
            if (scanf("%d %d", &start, &terminate) != 2)
            {
                fprintf(stderr, "Invalid instruction.\n");
                continue;
            }
            if (G -> last_mode == GRAPH :: NONE)
            {
                fprintf(stderr, "Invalid instruction.\n");
                continue;
            }
            print_length(G, start, terminate);
        }
        //PrintPath
        else if (strcmp(word, "PrintPath") == 0)
        {
            if (scanf("%d %d", &start, &terminate) != 2)
            {
                fprintf(stderr, "Invalid instruction.\n");
                continue;
            }
            if (G -> last_mode == GRAPH :: NONE)
            {
                fprintf(stderr, "Invalid instruction.\n");
                continue;
            }
            print_path(G, start, terminate, st);
        }
        else
        {
            fprintf(stderr, "Invalid instruction.\n");
        }
    }
}

