# Dijkstra Shortest Path

This project implements **Dijkstra’s Algorithm** in C++, using custom-built data structures such as:
- A binary **Min-Heap**
- An adjacency list–based **Graph**
- A manual **Stack**
- Custom parsing and utility functions

The program reads a graph from an input file and computes the **shortest path from every node to a specified destination node**.  
It supports both **directed** and **undirected** graphs.

This repository demonstrates mastery of:
- Low-level C++ programming (no STL vectors, no priority_queue)
- Manual dynamic memory management
- Custom data structures
- Graph processing
- Algorithm runtime analysis

---

## Features

### Core Functionality
- Reads graph definitions from `.txt` input files  
- Supports **DirectedGraph1** and **UndirectedGraph1** formats  
- Builds adjacency lists using dynamically allocated edges  
- Uses a manually implemented **Min-Heap priority queue**  
- Performs Dijkstra's shortest path algorithm  
- Reconstructs paths using a custom Stack  
- Prints both path cost and node traversal sequence  
- Clean error handling and input validation

---

## Example Graph File Format

8 14
1 1 2 10
2 1 4 5
3 2 3 1

Where each line represents:

<NumberofVertices> <NumberofEdges>
<EdgeId> <StartNode> <EndNode> <Weight>
<EdgeId> <StartNode> <EndNode> <Weight>
<EdgeId> <StartNode> <EndNode> <Weight>

## Runtime Complexity

### **Dijkstra’s Algorithm**
- **Time Complexity:** 
- O((V + E) log V)

Using Custom Min-Heap Implementation. 
- **Space Complexity:**
- O(V + E)

## Other Runtime Complexity

### **Custom Min-Heap**
- Insert: `O(log n)`  
- Extract-Min: `O(log n)`  
- Build Heap: `O(n)`  

### **Adjacency List Graph**
- Construction: `O(V + E)`  
- Memory: `O(V + E)`  

### **Stack**
- Push: `O(1)`  
- Pop: `O(1)`

## 📂 Project Structure
├── graph.cpp / graph.h # Adjacency list + graph utilities
├── heap.cpp / heap.h # Min-Heap implementation
├── stack.cpp / stack.h # Stack for path reconstruction
├── util.cpp / util.h # File parsing, helpers
├── data_structures.h # Shared struct definitions
├── main.cpp # Entry point
├── graphs/ # Test graph files (modified for public posting)
├── Makefile # Build instructions
└── .gitignore # Ignore build artifacts & IDE files
---

## 🛠️ How to Build

### **With Makefile (recommended)**

```bash
make
./dijkstra
```
This produces an executable named: ./dijkstra

### How to Run

- Arguments: ./dijkstra <InputFile> <GraphType> <Flag>

- Directed Graph Example: ./dijkstra graphs/network02.txt DirectedGraph 1
- Undidrected Graph Example: ./dijkstra graphs/network02.txt UndirectedGraph 1

* will write "Usage: ./dijkstra <InputFile> <GraphType> <Flag> to stderr for incorrect arguments
* Flag is either 1 or 0

### Flag 
* If the graph is directed and flag is 1,insert the corresponding node for edge (u, v) at the rear of ADJ[u]
* If the graph is undirected and flag is 1, insert a corresponding node for edge (u, v) at the rear of ADJ[u], and
insert a corresponding node for edge (v, u) at the rear of ADJ[v].
* If the graph is directed and flag is 0, insert the corresponding node for edge (u, v) at the front of ADJ[u].
* If the graph is undirected and flag is 0, insert a corresponding node for edge (u, v) at the front of ADJ[u], and insert a corresponding
node for edge (v, u) at the front of ADJ[v].

### Graphs

- Network1: 8 vertices 14 edges
- Network2: 8 vertices 11 edges
- Network3: 175813 vertices 179179 Edges

#### Commands
- Stop :Program stops
- PrintADJ :Prints Adjacency list of input graph to stdout.
- SinglePair <source> <destination> :finds shortest path from source to destination 
- SingleSource <source> :finds shortest path from source to ALL other nodes
- PrintLength <s> <t> :Prints the length of the shortest path from source to destination 
- PrintPath <s> <t> :Prints shortest path from source to destination 

* waits for next instruction until Stop
* states if there is no path
* will write "Invalid instruction" to stderr and wait for new instruction

### Sample Outputs:

The shortest path from 1000 to 1010 is:
[1000: 0.00]-->[1004: 1.24]-->[1006: 3.54]-->[1010: 7.15]

The length of the shortest path from 1 to 5 is: 7.00

There is no path from 1 to 8.


##### Academic Notes 
This was the final project for Data Structures and Algorithms Class
