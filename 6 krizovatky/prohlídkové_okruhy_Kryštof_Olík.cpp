#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

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
    while (!q.empty()) {
        //Dát pryč první křižovatku
        int v = q.front();
        q.pop();
 
        //Pokud se najde destinace křižovatka
        if (v == dest) {
            return true;
        }
 
        //Iterovat přes všechny hrany mezi křižovatky 
        for (int u: graph.adjList[v]) {
            if (!discovered[u]) {
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

    //Parsneme vstupní data do vektorů
    string line;
    getline(cin,line);
    M = line[0] - '0';
    N = line[2] - '0';
    O = line[4] - '0';

    //nahrát hrany
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        int src = line[0] - '0' - 1;
        int dest = line[2] - '0' - 1;
        hrany.push_back({src,dest});
    }
    //nahrát otazky
    for (int i = 0; i < O; i++) {
        getline(cin, line);
        int src = line[0] - '0' - 1;
        int dest = line[2] - '0' - 1;
        otazky.push_back({src,dest});
    }
 
    //postavíme graf ze zadaných hran
    Graph graph(hrany, M);
    
    //iterace přes otázky
    for (Edge edge : otazky) {   
        //Provedeme BFS přes graf a zjistíme, zda se dá z křižovatky src dostat do křižovatky dest, poté zapíšeme výsledek
        if (isReachable(graph, edge.src, edge.dest)) {
            cout << "Cesta existuje" << endl;
        }
        else {
            cout << "Cesta neexistuje" << endl;
        }
    }
 
    return 0;
}