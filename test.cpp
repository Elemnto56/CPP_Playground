#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;

struct Instr {
    
};


int main(int argc, char** argv) {
    vector<string> args;
    if (argc != 2) {cerr << "Too many or too little args given\n"; return 1;}
    for (int i=1; i < argc; i++) args.push_back(string{argv[i]});
    if (!filesystem::exists(args[0])) {cerr << args[0] + " is not a valid bytecode file\n"; return 1;}

    ifstream bc_file(args[0]);
    vector<Instr> bc;
    string line;

    while (getline(bc_file, line)) {

    }
}

int executor(vector<Instr> bc) {

}