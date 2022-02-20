#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Mesto {
    unsigned int id;
    public:
        vector<Mesto*> vyjezdy;
        unordered_map<unsigned int,Mesto*> vyjezdy_map;
        Mesto(unsigned int id) {
            this->id = id;
        }
        //find_id=jaky mesto najit; cesta=jaky mesta uz navstivil
        Mesto bfs(unsigned int find_id,vector<Mesto*> cesta) {
            //found it 
            if (vyjezdy_map.find(find_id) != vyjezdy_map.end()) return *vyjezdy_map.find(find_id)->second;
            //didnt find it
            else {

                return *this;
            }
        }
};

//Funkce která čte řádek standartního vstupu a načítá ho do vektoru čísel
vector<unsigned int> fiks_parser() {
	string line;
    vector<unsigned int> input;
    getline(cin,line);
	string space_delimiter = " ";
    size_t pos = 0;
    while ((pos = line.find(space_delimiter)) != string::npos) {
		unsigned int num = stol(line.substr(0, pos));
        input.push_back(num);
        line.erase(0, pos + space_delimiter.length());
    }
    unsigned int lline = stoul(line);
	input.push_back(lline);

	return input;
}

int main() {
    vector<unsigned int> in = fiks_parser();
    unsigned int N = in[0];
    unsigned int Q = in[1];
    unordered_map<unsigned int,Mesto*> mesta_map;

    //load mesta_map a vyjezdy
    for (unsigned int i = 0; i < N-1; i++) {
        in = fiks_parser();
        unsigned int from = in[0];
        unsigned int to = in[1];

        //create first city 
        auto srch_from = mesta_map.find(from);
        if (srch_from == mesta_map.end()) {
            Mesto *mesto = new Mesto(from);
            mesta_map[from] = mesto;
            srch_from = mesta_map.find(from);
        }

        //create second city
        auto srch_to = mesta_map.find(to);
        if (srch_to == mesta_map.end()) {
            Mesto *mesto = new Mesto(to);
            mesta_map[to] = mesto;
            srch_to = mesta_map.find(to);
        }
        
        //spojit mesta_map pokud tam jeste neni ulozeno
        Mesto *mesto_from = srch_from->second;
        Mesto *mesto_to = srch_to->second;
        if (mesto_from->vyjezdy_map.find(to) == mesto_from->vyjezdy_map.end()) {
            mesto_from->vyjezdy.push_back(mesto_to);
            mesto_from->vyjezdy_map[to] = mesto_to;
        }
        if (mesto_to->vyjezdy_map.find(from) == mesto_to->vyjezdy_map.end()) {
            mesto_to->vyjezdy.push_back(mesto_from);
            mesto_to->vyjezdy_map[from] = mesto_from;
        }
    }

    //
    for (unsigned int i = 0; i < Q; i++) {
        in = fiks_parser();
        unsigned int K = in[0];
        for (unsigned int Ki = 0; Ki < K; Ki++) {
            unsigned int from_mesto_id = in[Ki+1];
            auto from_mesto = mesta_map[from_mesto_id];
        }
    }
}
