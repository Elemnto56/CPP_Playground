#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>

bool flag_check(std::vector<std::string> args, std::string to_find) {for (std::string_view arg : args) if (arg == to_find) return true; return false;}

int main(int argc, char* argv[]) {
    std::vector<std::string> args, lines, full_row;
    if (argc > 2 || argc < 2) {std::cerr << "Usage:\n csvparse [filename.csv]\n"; return 1;}
    for (int i=1; i < argc; i++) args.push_back(argv[i]);
    if (!std::filesystem::exists(args[0])) {std::cerr << args[0] << " does not exist\n"; return 1;}

    std::ifstream csv(args[0]);
    std::string line;
    while (std::getline(csv, line)) lines.push_back(line);

    // Each vector in the main vector will be each row (line) from the .csv
    std::vector<std::vector<std::string>> cols_rows;

    if (flag_check(args, "--interact")) {
        
    }
    else {
        std::string piece;
        for (int j{}; j < lines.size(); j++) {
            std::istringstream row(lines[j]);

            while (std::getline(row, piece, ',')) full_row.push_back(piece);
            cols_rows.push_back(full_row);
            full_row.clear();
        }
        
        for (int k{}; k < cols_rows.size(); k++) {
            std::cout << "| ";
            for (auto cell : cols_rows[k]) std::cout << cell << " | ";
            std::cout << std::endl;
            if (k == 0) std::cout << "  --------- \n";
        }
    }
}