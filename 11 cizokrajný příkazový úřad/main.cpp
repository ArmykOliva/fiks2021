#include <iostream>
using namespace std;

unsigned int PC; //8bit, urcuje co ma dalsi proces delat, kazda instrukce PC++;, mod 256
unsigned int pamet[256]; //sdilena pamet procesu s 32bit cislama, cyklicka pamet: 257=1, adresa 0 = 0 nejde zmenit, 666= chyba

struct Instrukce {
    unsigned int instrukce; //8bit
    unsigned int argument; //16bit
    //zbylych 8bitu je ignored
};

class Process {
    public:
        bool alive = true;
        int stack[16]; //16 32bit cisel, ukoncit pokud pretece
        int do_instruction(unsigned int instruction,unsigned int argument = 0;) {
            switch(instruction) {
                case 0:
                    cout <<"yes" <<endl;
                break;
            };
            cout << instruction << endl;
            return 0;
        };
};

int main() {
    PC = 256;
    Process proc;
    proc.do_instruction(0);
    cout<<PC<<endl;
    return 0;
}