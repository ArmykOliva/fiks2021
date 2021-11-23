#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
//O(V+E) where V and E are the total number of verticies and hrany in the graph

//Hrana křižovatky
struct Edge {
    int src, dest;
};
 
//Objekt na graf
class Graph
{
    public:
        // vektor vektorů, který reprezentuje adjacency list
        vector<vector<int>> adjList;
    
        //Constructor
        Graph(vector<Edge> const &hrany, int M)
        {
            //zvětšit dynamicky adjList aby mohl držet M počet vektorů<int>
            adjList.resize(M);
    
            //přidat hrany do adjacency listu
            for (auto &edge: hrany) {
                adjList[edge.src].push_back(edge.dest); //Z každého source jsou uloženy všechny možné destinace 
            }
        }
};
 
//Funkce, která provede BFS ze source křižovatky v grafu a zjistí, zda existuje cesta do křižovatky dest.
bool isReachable(Graph const &graph, int src, int dest)
{
    //Počet křižovatek
    int M = graph.adjList.size();
 
    //pamatovat si jestli se křižovatka našla nebo ne
    vector<bool> discovered(M);
 
    //Udělat queue na BFS
    queue<int> q;
 
    //source křižovatka se našla hned od začátku
    discovered[src] = true;
 
    //dát do queue soruce křižocatku
    q.push(src);
 
    //iterovat dokud nebude queue prázdná
    while (!q.empty())
    {
        //Dát pryč první křižovatku
        int v = q.front();
        q.pop();
 
        //Pokud se najde destinace křižovatka
        if (v == dest) {
            return true;
        }
 
        //Iterovat přes všechny hrany mezi křižovatky 
        for (int u: graph.adjList[v])
        {
            if (!discovered[u])
            {
                //dát tuto křižovatku do queue
                discovered[u] = true;
                q.push(u);
            }
        }
    }
 
    return false;
}
 
int main()
{
    vector<Edge> hrany; //hrany křižovatek
    vector<Edge> otazky; //otázky na cesty
    int M, N, O; //pocet krizovatek, pocet cest, pocet otazek

    //Otevřeme input.txt a parsneme data do vektorů
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        getline(file,line);
        M = line[0] - '0';
        N = line[2] - '0';
        O = line[4] - '0';

        //hrany
        for (int i = 0; i < N; i++) {
            getline(file, line);
            int src = line[0] - '0' - 1;
            int dest = line[2] - '0' - 1;
            hrany.push_back({src,dest});
        }
        //otazky
        for (int i = 0; i < O; i++) {
            getline(file, line);
            int src = line[0] - '0' - 1;
            int dest = line[2] - '0' - 1;
            otazky.push_back({src,dest});
        }
    }
    file.close();
 
    //postavíme graf ze zadaných hran
    Graph graph(hrany, M);
    
    //Otevřeme output.txt, provedeme BFS a napíšeme výsledek
    ofstream myfile("output.txt");
    if (myfile.is_open()) {
        //iterace přes otázky
        for (Edge edge : otazky) {   
            //Provedeme BFS přes graf a zjistíme, zda se dá z křižovatky src dostat do křižovatky dest
            if (isReachable(graph, edge.src, edge.dest)) {
                myfile << "Cesta existuje" << endl;
            }
            else {
                myfile << "Cesta neexistuje" << endl;
            }
        }
    }
    file.close();
 
    return 0;
}