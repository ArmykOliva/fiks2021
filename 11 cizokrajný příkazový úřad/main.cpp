#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

struct Instruction {
    unsigned int command; //8bit
    unsigned int argument; //16bit
    //zbylych 8bitu je ignored
};

vector<unsigned long> pamet; //sdilena pamet procesu s 32bit cislama, cyklicka pamet: 257=1, adresa 0 = 0 nejde zmenit, 666= chyba

unsigned int my_power(unsigned int base, unsigned int exp) {
    unsigned int result = 1;
    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

class Process {
    public:
        unsigned int PC; //8bit, urcuje co ma dalsi proces delat, kazda instrukce PC++;, mod 256
        bool alive = true;
        vector<unsigned long> stack; //16 32bit cisel, ukoncit pokud pretece``~

        //parse decimal to instruction
        Instruction get_instruction(unsigned int dec) {
            string bin32  = "00000000000000000000000000000000";
            for (int pos = 31; pos >= 0; --pos) {
                if (dec % 2) bin32[pos] = '1';
                dec /= 2;
            }
            unsigned int argument = stoi(bin32.substr(8,16),0,2);
            unsigned int command = stoi(bin32.substr(24,8),0,2);
            Instruction instruction = {command,argument};
            return instruction;
        };

        void add_stack(unsigned long value) {
            if (stack.size() < 16) {
                stack.push_back(value);
            } else {
                alive = false;
            }
        }
        void pop_stack() {
            if (stack.size() > 0) stack.pop_back();
            else alive = false;
        }
        unsigned long read_stack() {
            if (stack.size() > 0) {
                unsigned long value = stack.back();
                pop_stack();
                return value;
            } else {
                alive = false;
                return 0;
            }
        }
        unsigned long read_stack_no_pop() {
            if (stack.size() > 0) {
                unsigned long value = stack.back();
                return value;
            } else {
                alive = false;
                return 0;
            }
        }

        int simulate();
};

vector<Process*> teleport; //jake pointery na procesy jsou v teleportu

int Process::simulate() {
    if (!alive) return -1; //dead dont do anything

    ////cout  << "PC " << PC << endl;
    Instruction instruction = get_instruction(pamet[PC]);
    
    if (instruction.command == 0) {
        //cout <<"NOP"<<endl;
    }
    else if (instruction.command == 1) {
        ////cout  <<"PC"<<endl;
        add_stack(PC);
    }
    else if (instruction.command == 2) {
        ////cout  <<"PUSH "<<instruction.argument<<endl;
        add_stack(instruction.argument);
    }
    else if (instruction.command == 3) {
        ////cout  <<"POP"<<endl;
        pop_stack();
    }
    else if (instruction.command == 4) {
        ////cout  <<"SWAP"<<endl;
        if (stack.size() >= 2) swap(stack[stack.size()-2],stack[stack.size()-1]);
        else alive = false;
    }
    else if (instruction.command == 5) {
        ////cout  <<"DUP"<<endl;
        add_stack(read_stack_no_pop());
    }
    else if (instruction.command == 6) {
        ////cout  <<"PUSHSSZ"<<endl;
        add_stack(stack.size());
    }
    else if (instruction.command == 7) {
        ////cout  <<"LOAD"<<endl;
        unsigned int adresa = read_stack();
        if (adresa == 666) {
            alive = false;
        }
        add_stack(pamet[adresa % 256]);
    }
    else if (instruction.command == 8) {
        ////cout  <<"STORE"<<endl;
        unsigned int adresa = read_stack();
        unsigned int hodnota = read_stack();
        if (adresa == 666) {
            alive = false;
        } else if (adresa % 256 != 0) {
            pamet[adresa % 256] = hodnota;
        }
    }
    else if (instruction.command == 9) {
        ////cout  <<"ADD"<<endl;
        unsigned int i1 = read_stack();
        unsigned int i2 = read_stack();
        add_stack(i1+i2);
    }
    else if (instruction.command == 10) {
        ////cout  <<"SUB"<<endl;
        unsigned int i1 = read_stack();
        unsigned int i2 = read_stack();
        add_stack(i1-i2);
    }
    else if (instruction.command == 11) {
        ////cout  <<"DIV"<<endl;
        unsigned int i1 = read_stack();
        unsigned int i2 = read_stack();
        if (i2 == 0) alive = false;
        else add_stack(i1/i2);
    }
    else if (instruction.command == 12) {
        ////cout  <<"POW"<<endl;
        unsigned int i1 = read_stack();
        unsigned int i2 = read_stack();
        unsigned int result;
        if (i1 == 0 && i2 == 0) result = 1;
        else result = my_power(i1,i2);
        add_stack(result);
    }
    else if (instruction.command == 13) {
        //cout  <<"BRZ "<<instruction.argument<<endl;
        unsigned int i1 = read_stack();
        if (alive && i1 == 0) {
            PC += instruction.argument;
        }
    }
    else if (instruction.command == 14) {
        //cout  <<"BR3 "<<instruction.argument<<endl;
        unsigned int i1 = read_stack();
        if (alive && i1 == 3) {
            PC += instruction.argument;
        }
    }
    else if (instruction.command == 15) {
        //cout  <<"BR7 "<<instruction.argument<<endl;
        unsigned int i1 = read_stack();
        if (alive && i1 == 7) {
            PC += instruction.argument;
        }
    }
    else if (instruction.command == 16) {
        //cout  <<"BRGE "<<instruction.argument<<endl;
        unsigned int i1 = read_stack();
        unsigned int i2 = read_stack();
        if (alive && i1 >= i2) {
            PC += instruction.argument;
        }
    }
    else if (instruction.command == 17) {
        //cout  <<"JMP "<<instruction.argument<<endl;
        PC = instruction.argument; 
    }
    else if (instruction.command == 18) {
        ////cout  <<"ARMED_BOMB"<<endl;
        alive = false;
    }
    else if (instruction.command == 19) {
        ////cout  <<"BOMB"<<endl;
        pamet[PC] = 18;
    }
    else if (instruction.command == 20) {
        ////cout  <<"TLPORT"<<endl;
        if (PC == 0) PC = 255; else PC --;
        teleport.push_back(this);
    }
    else if (instruction.command == 21) {
        ////cout  <<"JNTAR"<<endl;
        pamet[(PC-2)%256] = 19;
        pamet[(PC-4)%256] = 19;
        pamet[(PC-8)%256] = 19;
        pamet[(PC+2)%256] = 19;
        pamet[(PC+4)%256] = 19;
        pamet[(PC+8)%256] = 19;
    } else {
        alive = false;
    }
    
    if (alive && PC == 666) alive = false;
    if (alive) PC = (PC + 1) % 256;
    else PC = PC % 256;
    return 0;
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

int main() {
    vector<unsigned long> in = fiks_parser();
	int Q = in[0];
    //iterace pres zadani
    for (int zadani = 0; zadani < Q; zadani++) {
        //fill memory with empty
        int pamet_size = 256;
        pamet.clear();
        for (int i = 0; i < pamet_size; i++) {
            pamet.push_back(0);
        }

        //create processes and load memory
        vector<Process> processes;

        in = fiks_parser();
        int P = in[0];
        for (int proces = 0; proces < P; proces++) {
            in = fiks_parser();
            //create process
            Process process;
            process.PC = in[0] % 256;
            unsigned int n = in[1];
            //load instruction number into memory
            for (unsigned int ni = 2; ni < n+2; ni++) {
                /*Instruction blah = process.get_instruction(in[ni]);
                cout << blah.command << " ; " << blah.argument << " ; " << in[ni] <<  endl;*/
                pamet[(process.PC+ni-2)%256] = in[ni];
            }
            processes.push_back(process);
        }
        pamet[0] = 0;
        
        //simulate processes
        for (int cykl = 0; cykl < 5000; cykl++) {
            for (Process &process : processes) {
                process.simulate();
            }

            //teleporty
            if (teleport.size() > 1) {
                unsigned int first_PC = teleport[0]->PC+1;
                for (int i = 0; i < teleport.size()-1; i++) {
                    teleport[i]->PC = teleport[i+1]->PC+1;
                }
                teleport[teleport.size()-1]->PC = first_PC;
            }
            teleport.clear();
        }

        //write
        unsigned int PCs = 0;
        for (Process &process : processes) {
            PCs += process.PC;
        }
        cout << pamet[42] << " " << PCs << endl;
    }
    return 0;
}