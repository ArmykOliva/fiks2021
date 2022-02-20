// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
#include<iostream>
#include <list>
#include <vector>
#include <string>
 
using namespace std;
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
 
    // Pointer to an array containing adjacency
    // lists
    list<int> *adj;  
public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int v, int w);
 
    // prints BFS traversal from a given source s
    void BFS(int s); 
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

//Funkce která čte řádek standartního vstupu a načítá ho do vektoru čísel
vector<unsigned long> fiks_parser() {
	string line;
    vector<unsigned long> input;
    getline(cin,line);
	string space_delimiter = " ";
    size_t pos = 0;
    while ((pos = line.find(space_delimiter)) != string::npos) {
		unsigned long num = stol(line.substr(0, pos));
        input.push_back(num);
        line.erase(0, pos + space_delimiter.length());
    }
    unsigned long lline = stoul(line);
	input.push_back(lline);

	return input;
}
 
// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    vector<unsigned long> in = fiks_parser();
    unsigned long N = in[0];
    unsigned long Q = in[1];

    //load mesta a vyjezdy
    for (unsigned long i = 0; i < N-1; i++) {
        in = fiks_parser();
        unsigned long from = in[0];
        unsigned long to = in[1];
        g.addEdge(from,to);
        g.addEdge(to,from);
    }
 
    g.BFS(3);
 
    return 0;
}