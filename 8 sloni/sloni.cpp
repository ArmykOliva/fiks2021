#include <iostream>
#include <tgmath.h>
using namespace std;

int sloni_line(int w, int x, int T) {
    int sudy = T % 2 == 0;
    unsigned long long pozice;
    if (sudy) {
        int width_pravo = floor((w-x)/2);
        int width_levo = floor(x/2);
        pozice = min(T/2,width_pravo) + min(T/2,width_levo) + 1;
    } else {
        int width_pravo = ceil(((double)w-(double)x)/2);
        int width_levo = ceil((double)x/2);
        int half_T = ceil(double(T)/2);
        pozice = min(half_T,width_pravo) + min(half_T,width_levo);
    }
    return pozice;
}
long long sloni(int w, int h, int x, int y, int T) {
    long long pozice = 0;
    h -= 1;
    w -= 1;
    
    //pocitani rovny line
    pozice += sloni_line(w,x,T);

    //pocitani dolu
    for (int i = 1; i <= y; i++) {
        if (T-i < 0) break;
        pozice += sloni_line(w,x,T-i);
    }

    //pocitani nahoru
    for (int i = 1; i <= h-y; i++) {
        if (T-i < 0) break;
        pozice += sloni_line(w,x,T-i);
    }

    return pozice;
}

int main() {
    string line;
    getline(cin,line);
    int N = stoi(line);

    for (int i = 0; i < N; i++) {
        int in[5];
        int oldfound = -1;
        getline(cin,line);
        for (int j = 0; j < sizeof(in)/sizeof(int); j ++) {
            int found = line.find(" ",oldfound+1);
            string substr = line.substr(oldfound+1,found);
            oldfound = found;
            in[j] = stoi(substr);
        }
        cout << sloni(in[0],in[1],in[2],in[3],in[4]) << endl; 
    }
    return 0;
}