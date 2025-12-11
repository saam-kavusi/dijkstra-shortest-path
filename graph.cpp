// Saam Kavusi
// 1229746585

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>

#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"

//helpers to determine graph type
static bool undirected_graph_check(const char* graphType)
{
    return (graphType && strcmp(graphType, "UndirectedGraph") == 0);
}

//helpers to insert at front or rear
static void insert_front(pNODE& head, int u, int v, double w, int edgeIndex)
{
    //allocate memory to insert at front of list u
    pNODE node = (pNODE) calloc(1,sizeof(NODE));

    if (!node) {return;} //memory allocation check

    node -> index = edgeIndex; // original index from input
    node -> u     = u;         // source
    node -> v     = v;         // destination
    node -> w     = w;         // weight
    node->next    =  head;     // inserting at head u
    head          = node;      // update head to new node

}

static void insert_rear(pNODE& head, int u, int v, double w, int edgeIndex)
{
    pNODE node = (pNODE) calloc(1, sizeof(NODE));

    if (!node) {return;} //memory allocation check

    node -> index = edgeIndex; // original index from input
    node -> u     = u;         // source
    node -> v     = v;         // destination
    node -> w     = w;         // weight
    node->next    = nullptr;   // inserting at tail

    if (!head){ head = node; return; }

    pNODE temp = head;
    while (temp -> next) {temp = temp -> next;}
    temp -> next = node;
}

//helper to reset vertices for Dijkstra
static void vertex_reset(GRAPH* G)
{
    int i;

    for ( i = 1; i <= G -> n; i++ )
    {
        G -> V[i] -> key      = DBL_MAX; //infinity
        G -> V[i] -> pi       = -1;      // represents NIL (pi is int)
        G -> V[i] -> color    = WHITE;
        G -> V[i] -> position = 0;
    }
}

// helper to free graph space
static void free_graph_on_error(GRAPH* G, int vertexMem)
{
    int i;          // counter
    pNODE current;  // current node for Adj list
    pNODE temp;     // temp node for Adj list

    if (G -> V) // free mem for allocated Vertices
    {
        for ( i = 1; i <= vertexMem; i++ )
        {
            if (G -> V[i]) {free(G -> V[i]);}
        }
        free(G -> V);
    }

    if (G -> Adj) // free mem for adj list
    {
        for ( i = 1; i <= G -> n; i++ ) // go through list
        {
            current = G -> Adj [i];
            while (current) // free list
            {
                temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(G -> Adj); // free Adj
    }
    free(G); // free graph
}

//print path/length helper - refer to most recent dijkstra
static bool can_we_print(const GRAPH* G, int start, int terminate)
{
    if (G -> last_mode == GRAPH::SINGLE_PAIR)
    {
        return (start == G -> last_source) && (terminate == G -> last_destination);
    }
    if (G -> last_mode == GRAPH::SINGLE_SOURCE)
    {
        return (start == G -> last_source);
    }

    return false;
}

//relax function
static void relax(GRAPH* G, pVERTEX u, int v, double w, HEAP* heap)
{
    if (G -> V[v] -> color == BLACK) return;

    const double distance = u -> key + w;

    if (G -> V[v] -> color == WHITE)
    {
        G -> V[v] -> color = GRAY;
        if (distance < G -> V[v] -> key)
        {
            G -> V[v] -> key = distance;
            G -> V[v] -> pi = u -> index;
        }
        heap_insert(heap, G -> V[v]); // new discovery
    }
    else if (G -> V[v] -> color == GRAY)
    {
        if (distance < G -> V[v] -> key) // improvement means decrease key using position
        {
            G -> V[v] -> key = distance;
            G -> V[v] -> pi = u -> index;
            heap_decrease_key(heap, G -> V[v] -> position, G -> V[v] -> key);
        }
    }
}

// Loads graph from file; builds internal structures according to GraphType × Flag.
GRAPH* load_graph(const char* filename, const char* graphType, int flag)
{
    int n; // vertices
    int m; // edges
    int i; // counter

    int edgeIndex;
    int u; // start edge
    int v; // end edge
    double w; // weight

    FILE* file = fopen(filename, "r");
    if (!file) {return nullptr;}

    if (fscanf(file, "%d %d", &n, &m) != 2 || n <= 0 || m < 0)
    {
        fclose(file);
        return nullptr;
    }

    GRAPH* G = (GRAPH*) calloc(1, sizeof(GRAPH));
    if (!G) {fclose(file); return nullptr;}
    G -> n = n;
    G -> m = m;
    G -> last_mode = GRAPH::NONE;
    G -> last_source = -1;
    G -> last_destination = -1;

    // allocate and initialize Vertex
    G -> V = (pVERTEX*) calloc(n + 1, sizeof(pVERTEX));
    if (!G -> V)
    {
        fclose(file);
        free(G);
        return nullptr;
    }

    for (i = 1; i <= n; i++)
    {
        G -> V[i] = (pVERTEX) calloc(1, sizeof(VERTEX));
        if (!G -> V[i])
        {
            fclose(file);
            free_graph_on_error(G, i - 1);
            return nullptr;
        }

        G -> V[i] -> index     = i;
        G -> V[i] -> color     = WHITE;
        G -> V[i] -> key       = DBL_MAX;
        G -> V[i] -> pi        = -1;
        G -> V[i] -> position  = 0;
    }

    // allocate and initialize adj list
    G -> Adj = (pNODE*) calloc(n + 1, sizeof(pNODE));
    if (!G -> Adj)
    {
        fclose(file);
        for (i = 1; i <= n; i++)
        {
            if (G -> V[i]) free(G -> V[i]);
        }
            free(G -> V);
            free(G);
            return nullptr;
    }

    const bool undirected = undirected_graph_check(graphType);

    // read edges
    for (i = 0; i < m; i++)
    {
        edgeIndex = 0;
        u = 0;
        v = 0;
        w = 0.0;

        if (fscanf(file, "%d %d %d %lf", &edgeIndex, &u, &v, &w) != 4)
        {
            fclose(file);
            for (int k = 1; k <= n; k++)
            {
                pNODE temp = G -> Adj[k];
                while (temp)
                {
                    pNODE nxt = temp -> next;
                    free(temp);
                    temp = nxt;
                }
            }
            free(G -> Adj);
            for ( int k = 1; k <= n; k++) {free(G -> V[k]);}
            free(G -> V);
            free(G);
            return nullptr;
        }
        if (flag == 0)
        {
            insert_front(G -> Adj[u], u, v, w, edgeIndex);
            if (undirected){insert_front(G -> Adj[v], v, u, w, edgeIndex);}
        }
        else // flag is 1
        {
            insert_rear(G -> Adj[u], u, v, w, edgeIndex);
            if (undirected){insert_rear(G -> Adj[v], v, u, w, edgeIndex);}
        }
    }
    fclose(file);
    return G;
}

// Frees all dynamic allocations associated with the graph.
void destroy_graph(GRAPH* G)
{
    int i;

    if (!G) return;

    if (G -> Adj)
    {
        for (i = 1; i <= G -> n; i++)
        {
            pNODE temp = G -> Adj[i];
            while (temp)
            {
                pNODE nxt = temp -> next;
                free(temp);
                temp = nxt;
            }
        }
        free(G -> Adj);
    }

    if (G -> V)
    {
        for (i = 1; i <= G -> n; i++) {free(G -> V[i]);}
        free(G -> V);
    }
    free(G);
}

// Prints adjacency lists with required formatting.
void print_adj(const GRAPH* G)
{
    int i;

    for (i = 1; i <= G -> n; i++)
    {
       printf("ADJ[%d]:", i);
       for (pNODE temp = G -> Adj[i]; temp != nullptr; temp = temp -> next)
       {
           printf("-->[%d %d: %4.2lf]", temp -> u, temp -> v, temp -> w);
       }
       printf("\n");
    }
}

// Runs Dijkstra single-pair with early stop.
void shortest_path_single_pair(GRAPH* G, int start, int terminate, HEAP* heap)
{
    if (!G || start < 1 || start > G -> n || terminate < 1 || terminate > G -> n) {return;}

    vertex_reset(G);
    heap_reset(heap);

    G -> V[start] -> key = 0.0;
    G -> V[start] -> color = GRAY;
    heap_insert(heap, G-> V[start]);

    while (!heap_empty(heap))
    {
        VERTEX* u = heap_extract_min(heap);
        if (!u) break;

        if (u -> index == terminate) // early stop
        {
            u -> color = BLACK;
            break;
        }

        for (pNODE edge = G -> Adj[u -> index]; edge != nullptr; edge = edge -> next)
        {
            relax(G, u, edge -> v, edge -> w, heap);
        }

        u -> color = BLACK;
    }

    G -> last_mode = GRAPH::SINGLE_PAIR;
    G -> last_source = start;
    G -> last_destination = terminate;
}

// Runs Dijkstra single-source (no early stop).
void shortest_path_single_source(GRAPH* G, int start, HEAP* heap)
{
    if (!G || start < 1 || start > G -> n) {return;}

    vertex_reset(G);
    heap_reset(heap);

    G -> V[start] -> key = 0.0;
    G -> V[start] -> color = GRAY;
    heap_insert(heap, G-> V[start]);

    while (!heap_empty(heap))
    {
        VERTEX* u = heap_extract_min(heap);
        if (!u) break;

        for (pNODE edge = G -> Adj[u -> index]; edge != nullptr; edge = edge -> next)
        {
            relax(G, u, edge -> v, edge -> w, heap);
        }

        u -> color = BLACK;
    }

    G -> last_mode = GRAPH::SINGLE_SOURCE;
    G -> last_source = start;
    G -> last_destination = -1;
}

// Prints the shortest path if valid; otherwise prints required "no path" line.
void print_path(GRAPH* G, int start, int terminate, STACK* st)
{
    int currentVertex;
    int vertexIndex;

    if (!can_we_print(G, start, terminate)) //invalid request
    {
        return;
    }
    // valid request but unreachable
    if (start != terminate && G -> V[terminate] -> pi == -1)
    {
        printf("There is no path from %d to %d.\n", start, terminate);
        return;
    }

    // reconstrcting st
    stack_clear(st);

    currentVertex = terminate;
    while (currentVertex != -1)
    {
        push(st, currentVertex);
        if (currentVertex == start) break;
        currentVertex = G -> V[currentVertex] -> pi;
    }

    //output the shortest path
    printf("The shortest path from %d to %d is:\n", start, terminate);

    // print nodes in order
    while (!empty(st))
    {
        vertexIndex = pop(st);
        printf("[%d:%8.2lf]", vertexIndex, G -> V[vertexIndex] -> key);
        if (!empty(st)) printf("-->");
        else  printf(".\n");
    }
}

// Prints the length if valid; otherwise prints required "no path" line.
void print_length(GRAPH* G, int start, int terminate)
{
    if (!can_we_print(G, start, terminate))
    {
        printf("There is no path from %d to %d.\n", start, terminate);
        return;
    }
    if (start != terminate && G -> V[terminate] -> pi == -1)
    {
        printf("There is no path from %d to %d.\n", start, terminate);
        return;
    }
    printf("The length of the shortest path from %d to %d is: %8.2lf\n", start, terminate, G -> V[terminate] -> key);
}
