#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
using namespace std;

class Mesto {
    public:
        unsigned int id;
        unsigned int cena_do_ceska;
        bool visited = false;
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

void dfs_set_ceny(Mesto* mesto_start) {
    list<Mesto*> queue;
    mesto_start->visited = true; // cesko
    mesto_start->cena_do_ceska = 0;
    queue.push_back(mesto_start);
    
    while (!queue.empty()) {
        Mesto* front_mesto = queue.front();
        //cout << "id: " << front_mesto->id << " cost:" << front_mesto->cena_do_ceska << endl;
        queue.pop_front();

        for (Mesto* mesto_adj : front_mesto->vyjezdy) {
            if (mesto_adj->visited == false) {
                mesto_adj->visited = true;
                mesto_adj->cena_do_ceska = front_mesto->cena_do_ceska + 1;
                queue.push_back(mesto_adj);
            }
        }
    }
}

int main() {
    vector<unsigned int> in = fiks_parser();
    unsigned int N = in[0];
    unsigned int Q = in[1];
    unsigned int city_count = 0;
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
            city_count ++;
        }

        //create second city
        auto srch_to = mesta_map.find(to);
        if (srch_to == mesta_map.end()) {
            Mesto *mesto = new Mesto(to);
            mesta_map[to] = mesto;
            srch_to = mesta_map.find(to);
            city_count++;
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

    ///cena do ceska bfs algoritmem
    dfs_set_ceny(mesta_map[1]);


    //iterovat dny
    for (unsigned int i = 0; i < Q; i++) {
        in = fiks_parser();
        unsigned int K = in[0];
        //prvni algo jestli K=1
        if (K == 1) {
            unsigned int from_mesto_id = in[1];
            Mesto* from_mesto = mesta_map[from_mesto_id];
            cout << from_mesto->cena_do_ceska << endl;
        } 
        //druhy algo jestli K>1
        else {
            //cena do ceska
            unsigned celkova_cena_do_ceska = 0;
            for (unsigned int Ki = 0; Ki < K; Ki++) {
                celkova_cena_do_ceska += mesta_map[in[Ki+1]]->cena_do_ceska;
            }

            //dfs 
            vector<unsigned int> ceny;
            for (unsigned int Ki = 0; Ki < K; Ki++) {
                unsigned int celkova_cena = 0;
                
                //set every city to visited = false
                for (auto& mesto : mesta_map) {
                    mesto.second->visited = false;
                }

                //dfs
                dfs_set_ceny(mesta_map[in[Ki+1]]);

                celkova_cena = mesta_map[1]->cena_do_ceska;

                ceny.push_back(celkova_cena);
            }
            

            cout << celkova_cena_do_ceska;
            for (unsigned int cena : ceny) {
                cout << " " << cena;
            }
            cout << endl;
        }
    }
}
